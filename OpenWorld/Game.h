#pragma once
#include <iostream>
#include <ctime>
#include "Player.h"
#include "Enemy.h"
#include <random>
#include <algorithm>


class Game
{
public:
	Game() :mainMenuChoice(0), playing(true), player(playerCreation()) {};

	// Operators

	// Functions
	int mainMenu();
	Player playerCreation();
	Enemy spawnEnemy(int difficulty, int terrain);
	void gameLoop();

	void printStats();
	void printInventory();

	int rollBetween(int lower, int higher);

	int getInputBetween(int lower, int higher);

	void travel();
	void fight( Enemy& enemy, bool playerInitialize );
	void run( Enemy& enemy );
	void wait( Enemy& enemy );

	// Accessors
	inline bool getPlaying() const { return playing; };

	// Modifiers

private:
	int mainMenuChoice;
	bool playing;
	Player player;
};

