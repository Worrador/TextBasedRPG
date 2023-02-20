#pragma once
#include "Character.h"
#include "ItemParser.h"

using enemyRarity = std::string_view;
constexpr std::array<std::pair<std::string_view, int>, 5> enemyRarityThresholds{
	{{RARITY_LEVEL_6, RARITY_ENEMY_TRESHOLD_6},
	 {RARITY_LEVEL_5, RARITY_ENEMY_TRESHOLD_5},
	 {RARITY_LEVEL_4, RARITY_ENEMY_TRESHOLD_4},
	 {RARITY_LEVEL_3, RARITY_ENEMY_TRESHOLD_3},
	 {RARITY_LEVEL_2, RARITY_ENEMY_TRESHOLD_2}} };

class Enemy : public Character
{
public:
	Enemy(const std::string& name, int hpMax, int dmgMax, int defence, int staminaMax, int aggressivity);

	// Operators
	Enemy& operator*(const int& scaleToLevel);

	Item getRandomItem(const itemRarity& rarityName);

	// Functions

	// Accessors
	inline int getExpDrop() const { return expDrop; };
	inline int getAggressivity() const { return aggressivity; };
	inline int getRarity() const { return rarity; };
	inline std::vector<Item>& getLootItems() { return lootItems; };

	// Modifiers
	inline void setExpDrop(int newExpDrop) { expDrop = newExpDrop; };

private:
	int expDrop;
	int aggressivity;

	int rarity;
	enemyRarity rarityName;
	std::vector<Item> lootItems;

	//std::vector<ItemDrop>
};

