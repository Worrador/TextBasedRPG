#pragma once
#include "ResourceParser.h"
#include "Menu.h"
#include <random>
#include <iostream>
#include <mmsystem.h>
#include <unordered_map>
#include <numeric>

// Define a specialization of std::hash for Place
namespace std {
	template<> struct hash<Place> {
		std::size_t operator()(const Place& p) const {
			// You can use any function that maps a Place to a std::size_t
			return std::hash<std::string>()(p.getName());
		}
	};
}

namespace std {
	template<> struct equal_to<Place> {
		bool operator()(const Place& p1, const Place& p2) const {
			return p1.getName() == p2.getName();
		}
	};
}

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
	Place& currentPlace;
	std::unordered_map<Place, std::vector<Place*>> map_graph;
};

