#pragma once
#include <random>

inline std::mt19937 randomNumberGenerator(std::random_device{}());

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

inline int getRandomBetween(int lower, int higher)
{
	std::uniform_int_distribution<> lin_dist(lower, higher);

	return lin_dist(randomNumberGenerator);
}