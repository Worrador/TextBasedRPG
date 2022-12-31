#pragma once
#include "ResourceParser.h"
#include "Menu.h"
#include <random>
#include <mmsystem.h>

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
	Item getRandomWeapon();
	Item getRandomArmor();

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
	std::vector<Item> shopItems;
	Settlement& currentSettlement;
	Place* WorldMap;
};

