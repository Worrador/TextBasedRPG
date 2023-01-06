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
	void addConnections(int point, int additionalNumberOfConnections);
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
	std::vector<Item> shopItems;
	int currentPoint = 0;
	std::mt19937 randomNumberGenerator;
	
	// Use vector for constant_time acces, as we only ned to populate once (list could be used otherwise, as the insertion is more efficient)
	std::vector<mapPoint> worldMap;
};

