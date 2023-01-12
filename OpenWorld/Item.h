#pragma once
#include "Role.h"
#include <algorithm>
#include <vector>
#include <map>

using itemType = std::string;
using itemRarity = std::string;

class Item
{
public:
	Item(const std::string& name, const std::vector<roleName>& roles, const itemType& itemType, int hpMax, int damageMax, int defence, int staminaMax);

	// Operators

	// Functions

	// Accessors
	inline std::string getName() const { return name; };
	inline std::vector<roleName> getRoles() const { return roles; };
	inline int getLevel() const { return level; };
	inline int getBuyGold() const { return buyGold; };
	inline int getSellGold() const { return sellGold; };
	inline int getHpMax()	const { return hpMax; };
	inline int getDamageMax() const { return damageMax; };
	inline int getDefence() const { return defence; };
	inline int getStaminaMax() const { return staminaMax; };
	inline itemType getItemType() const { return type; };
	inline int getRarityValue() const { return rarity; };
	inline itemRarity getRarityName() const { return rarityName; };

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


	static inline const std::map<itemRarity, int> itemRarityThresholds = {
		{"Uncommon", 750},
		{"Rare", 500},
		{"Epic", 250},
		{"Legendary", 100},
		{"Mythic", 50}
	};
};