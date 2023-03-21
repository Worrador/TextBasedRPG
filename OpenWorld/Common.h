#pragma once
#include <random>

inline std::mt19937 randomNumberGenerator(std::random_device{}());

// Game constants
constexpr auto FIGHT_REST_STAMINA_INCREMENT = 3;

// Item rarities
constexpr auto RARITY_LEVEL_6 = "Mythic";
constexpr auto RARITY_LEVEL_5 = "Legendary";
constexpr auto RARITY_LEVEL_4 = "Epic";
constexpr auto RARITY_LEVEL_3 = "Rare";
constexpr auto RARITY_LEVEL_2 = "Uncommon";
constexpr auto RARITY_LEVEL_1 = "Common";

constexpr auto RARITY_ITEM_TRESHOLD_6 = 50;
constexpr auto RARITY_ITEM_TRESHOLD_5 = 100;
constexpr auto RARITY_ITEM_TRESHOLD_4 = 250;
constexpr auto RARITY_ITEM_TRESHOLD_3 = 500;
constexpr auto RARITY_ITEM_TRESHOLD_2 = 750;

constexpr auto RARITY_ENEMY_TRESHOLD_5 = 500;
constexpr auto RARITY_ENEMY_TRESHOLD_6 = 250;
constexpr auto RARITY_ENEMY_TRESHOLD_4 = 1000;
constexpr auto RARITY_ENEMY_TRESHOLD_3 = 2000;
constexpr auto RARITY_ENEMY_TRESHOLD_2 = 3000;

// Chances
constexpr auto CHANCE_ENCOUNTER = 0.5;
constexpr auto CHANCE_WAIT_NO_ATTACK_BASE = 0.25;
constexpr auto CHANCE_REST_MUGGING = 0.33;
constexpr auto SETTLEMENT_TERRAIN_RATIO = 0.1;
constexpr auto CHANCE_LOOT = 0.2;


constexpr auto MAX_WORLD_MAP_SIZE = 150;

constexpr auto MAX_CONNECTION_SIZE_TERRAIN = 3;
constexpr auto MAX_CONNECTION_SIZE_SETTLEMENT = 5;
constexpr auto REST_SHARED_ROOM_PRICE_CHEAP = 4;
constexpr auto REST_PRIVATE_ROOM_PRICE_CHEAP = 6;
constexpr auto REST_PRIVATE_ROOM_PRICE_EXPENSIVE = 8;
constexpr auto REST_EXPENSIVE_INN_SETTLEMENT_SIZE_TRESHOLD = 4;

constexpr auto MAX_ENEMY_AGGRESSIVITY = 10;

constexpr auto SHOP_SIZE_MULTIPLIER = 2;


inline int getRandomBetween(int lower, int higher)
{
	std::uniform_int_distribution<> lin_dist(lower, higher);

	return lin_dist(randomNumberGenerator);
}

inline int getRandomWithChance(double chance)
{
	std::uniform_real_distribution<> real_dist(0, 1);

	double randomNumber = real_dist(randomNumberGenerator);

	if (randomNumber < chance)
		return 1;
	else
		return 0;
}
