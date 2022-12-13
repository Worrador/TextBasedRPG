#pragma once
#include "Enemy.h"
#include <random>
#include "Menu.h"

class Game
{
public:

	// Constructors
	Game() :mainMenuChoice(0), playing(true), player(menu.playerCreationMenu()) {};

	// Delete copy and move constructor to prevent copying or moving
	Game(const Game&) = delete;
	Game(Game&&) = delete;

	// Operators, delete assignment and move operator to prevent copying or moving
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	// Functions

	// Static method to return a reference to the single instance
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	Enemy spawnEnemy(int difficulty, int terrain);
	void gameLoop();

	void rest( int restOption );
	void buy();

	int rollBetween(int lower, int higher);


	void travel( int travelOption );
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

