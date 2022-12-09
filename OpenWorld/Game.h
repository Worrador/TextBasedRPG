#pragma once
#include <iostream>
#include <ctime>
#include "Player.h"
#include "Enemy.h"


class Game
{
public:
	Game() :mainMenuChoice(0), playing(true), player(playerCreation()) {};

	// Operators

	// Functions
	int mainMenu();
	Player playerCreation();
	void gameLoop();

	void printStats();
	void printInventory();

	void travel();
	void fight( Enemy& enemy);

	// Accessors
	inline bool getPlaying() const { return playing; };

	// Modifiers

private:
	int mainMenuChoice;
	bool playing;
	Player player;
};

