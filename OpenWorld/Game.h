#pragma once
#include <ctime>
#include "Enemy.h"
#include <random>
#include <algorithm>
#include "Menu.h"


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
	void shop();
	void buy();

	int rollBetween(int lower, int higher);


	void travel();
	void makeAttack(Character& attacker, Character& defender);
	void fight( Enemy& enemy, bool playerInitialize );
	void run( Enemy& enemy );
	void wait( Enemy& enemy );

	// Accessors
	inline bool getPlaying() const { return playing; };

	// Modifiers

private:
	int mainMenuChoice;
	bool playing;
	Menu menu;
	Player player;
};

