#pragma once
#include "ResourceParser.h"
#include <random>
#include "Menu.h"
#include <windows.h>
#include <mmsystem.h>

// Player is manipulated manipulated through this object
class Game
{
public:

	// Constructors
	Game() :mainMenuChoice(0), playing(true), player(menu.playerCreationMenu()), currentSettlement(ResourceParser::getInstance().getParsedSettlements()[rollBetween(0, (int)ResourceParser::getInstance().getParsedSettlements().size())])
	{
		// TODO: replace to cpp
		// Start palying music
		PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		DWORD leftVolume = 2000;
		DWORD rightVolume = 2000;
		waveOutSetVolume(NULL, (leftVolume << 16) | rightVolume);
		shopItems.emplace_back(getRandomWeapon());
		shopItems.emplace_back(getRandomWeapon());
		shopItems.emplace_back(getRandomWeapon());
		shopItems.emplace_back(getRandomArmor());
		shopItems.emplace_back(getRandomArmor());
	};

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
};

