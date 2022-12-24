#pragma once
#include "Enemy.h"
#include <random>
#include "Menu.h"
#include <windows.h>
#include <mmsystem.h>

// Player is manipulated manipulated through this object
class Game
{
public:

	// Constructors
	Game() :mainMenuChoice(0), playing(true), player(menu.playerCreationMenu()) 
	{
		// Start palying music
		PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		DWORD leftVolume = 500;
		DWORD rightVolume = 500;
		waveOutSetVolume(NULL, (leftVolume << 16) | rightVolume);
		shopItems.push_back(getRandomItem());
		shopItems.push_back(getRandomItem());
		shopItems.push_back(getRandomItem());
		shopItems.push_back(getRandomItem());
	};

	// Delete copy and move constructor to prevent copying or moving
	Game(const Game&) = delete;
	Game(Game&&) = delete;

	// Operators, delete assignment and move operator to prevent copying or moving
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	// Functions
	Item getRandomItem();

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
	std::vector<Item> shopItems;
};

