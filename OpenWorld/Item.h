#pragma once
#include "Role.h"
#include "Common.h"
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

	//LESSON: lets use the copy and swap idom for construction strong exception safe copies of objects
	// Operators
	Item& operator=(const Item& other) noexcept;


	// Functions
	friend void swap(Item& lhs, Item& rhs) noexcept;

	// Accessors
	const std::string& getName() const { return name; };
	const std::vector<roleName>& getRoles() const { return roles; };
	const int getLevel() const { return level; };
	const int getBuyGold() const { return buyGold; };
	const int getSellGold() const { return sellGold; };
	const int getHpMax()	const { return hpMax; };
	const int getDamageMax() const { return damageMax; };
	const int getDefence() const { return defence; };
	const int getStaminaMax() const { return staminaMax; };
	const itemType& getItemType() const { return type; };
	const int getRarityValue() const { return rarity; };
	const itemRarity getRarityName() const { return rarityName; };

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