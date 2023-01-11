#pragma once
#include "ResourceParser.h"
#include "Menu.h"
#include <random>
#include <iostream>
#include <mmsystem.h>
#include <numeric>
#include <queue>


// Pointer for the place, and a vector for the next places
using mapPoint = std::pair<std::unique_ptr<Place>, std::vector<int>>;

constexpr auto MENU_TYPE_TRAVEL = "Travel";
constexpr auto MENU_TYPE_MAP = "Map";
constexpr auto MENU_TYPE_REST = "Rest";
constexpr auto MENU_TYPE_PLAYER_SHEET = "Player sheet";
constexpr auto MENU_TYPE_SHOP_ARMOR = SHOP_TYPE_ARMOR;
constexpr auto MENU_TYPE_SHOP_WEAPON = SHOP_TYPE_WEAPON;
constexpr auto MENU_TYPE_SHOP_CONSUMABLE = SHOP_TYPE_CONSUMABLE;
constexpr auto MENU_TYPE_QUIT = "Quit";

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

	// Functions
	void addConnections(int point, int additionalNumberOfConnections);
	bool isValidTerrainChoice(int selectedTerrainIndex, int currentPlaceIndex);
	void generateWorldMap();

	// Static method to return a reference to the single instance
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	Enemy spawnEnemy();
	void gameLoop();

	void rest( int restOption );

	int rollBetween(int lower, int higher);


	void travel( int travelOption );
	void makeAttack(Character& attacker, Character& defender);
	void fight( Enemy& enemy, bool playerInitialize );
	void run( Enemy& enemy );
	void wait( Enemy& enemy );

	// Accessors

	// Modifiers

private:
	int mainMenuChoice;
	bool playing;
	Menu menu;
	Player player;
	int currentPoint = 0;
	int previousPoint = 0;
	
	// Use vector for constant_time acces, as we only ned to populate once (list could be used otherwise, as the insertion is more efficient)
	std::vector<mapPoint> worldMap;
	std::mt19937 randomNumberGenerator;
};

