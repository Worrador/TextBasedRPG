#pragma once
#include "EnemyParser.h"
#include "SettlementParser.h"
#include "TerrainParser.h"
#include "Menu.h"
#include <iostream>
#include <mmsystem.h>
#include <numeric>
#include <queue>

// Constants for main menu options
constexpr auto MENU_TYPE_TRAVEL				= "Travel";
constexpr auto MENU_TYPE_MAP				= "Map";
constexpr auto MENU_TYPE_REST				= "Rest";
constexpr auto MENU_TYPE_PLAYER_SHEET		= "Player sheet";
constexpr auto MENU_TYPE_SHOP_ARMOR			= SHOP_TYPE_ARMOR;
constexpr auto MENU_TYPE_SHOP_WEAPON		= SHOP_TYPE_WEAPON;
constexpr auto MENU_TYPE_SHOP_CONSUMABLE	= SHOP_TYPE_CONSUMABLE;
constexpr auto MENU_TYPE_QUIT				= "Quit";


enum class gameResult {
	Lose = -1,
	stillPlaying = 0,
	Win = 1
};


// Player is manipulated manipulated through this object
class Game
{
public:

	// Constructors
	Game();

	// Delete copy and move constructor to prevent copying or moving
	Game(const Game&) = delete;
	Game(Game&&) = delete;

	// Operators, delete assignment and move operator to prevent copying or moving
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	// LESSON: Static method to return a reference to the single instance
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}
	void gameLoop();

	[[nodiscard]] inline const gameResult& getResult() { return result; };

private:

	// Functions
	void addConnections(int point, int additionalNumberOfConnections);
	bool isValidTerrainChoice(int selectedTerrainIndex, int currentPlaceIndex);
	void generateWorldMap();
	void playMusic(bool isSettlement);

	Enemy spawnEnemy();

	void rest( int restOption );

	void travel( int travelOption );
	void makeAttack(Character& attacker, Character& defender);
	void fight( Enemy& enemy, bool playerInitialize );
	void run( Enemy& enemy );
	void wait( Enemy& enemy );

	// Accessors

	// Modifiers
	int mainMenuChoice;
	gameResult result = gameResult::stillPlaying;
	Menu menu;
	Player player;
	int currentPoint{};
	int previousPoint{};
	
	// Use vector for constant_time acces, as we only need to populate once (list could be used otherwise, as the insertion is more efficient)
	std::vector<mapPoint> worldMap;
};

