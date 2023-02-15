#pragma once
#include "Role.h"
#include "Common.h"
#include <algorithm>
#include <vector>
#include <array>

using itemType = std::string;
using itemRarity = std::string_view;
constexpr std::array<std::pair<std::string_view, int>, 5> itemRarityThresholds{
	{{RARITY_LEVEL_6, RARITY_ITEM_TRESHOLD_6},
	 {RARITY_LEVEL_5, RARITY_ITEM_TRESHOLD_5},
	 {RARITY_LEVEL_4, RARITY_ITEM_TRESHOLD_4},
	 {RARITY_LEVEL_3, RARITY_ITEM_TRESHOLD_3},
	 {RARITY_LEVEL_2, RARITY_ITEM_TRESHOLD_2}} };


class Item
{
public:
	Item(const std::string& name, const std::vector<roleName>& roles, const itemType& itemType, int hpMax, int damageMax, int defence, int staminaMax);

	// Operators

	// Functions

	// Accessors
	inline const std::string& getName() const { return name; };
	inline const std::vector<roleName>& getRoles() const { return roles; };
	inline const int getLevel() const { return level; };
	inline const int getBuyGold() const { return buyGold; };
	inline const int getSellGold() const { return sellGold; };
	inline const int getHpMax()	const { return hpMax; };
	inline const int getDamageMax() const { return damageMax; };
	inline const int getDefence() const { return defence; };
	inline const int getStaminaMax() const { return staminaMax; };
	inline const itemType& getItemType() const { return type; };
	inline const int getRarityValue() const { return rarity; };
	inline const itemRarity getRarityName() const { return rarityName; };

	// Modifiers

private:
	// const, the compiler will implicitly delete the copy assignment operator, 
	// as it is not possible to change the value of a const data member.
	std::string name;
	std::vector<roleName> roles;	// multiple classes could use it
	itemType type;
	int level;
	int sellGold;
	int hpMax;
	int damageMax;
	int defence;
	int staminaMax;
	int buyGold;
	int rarity;
	itemRarity rarityName;
};