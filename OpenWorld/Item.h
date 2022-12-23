#pragma once
#include "RoleInfo.h"
#include <algorithm>
#include <iostream>

using itemType = std::string;

class Item
{
public:
	Item(const std::string& name, const std::vector<Role>& roles, const itemType& itemType, int hpMax, int damageMax, int defence, int staminaMax) :
		name(name), roles(roles), itemType(itemType),level((int)std::floor((hpMax + damageMax + defence + staminaMax) / 2)), hpMax(hpMax),
		buyGold(hpMax * 2 + damageMax * 2 + defence * 3 + staminaMax), sellGold((int)std::floor(buyGold / 2)), damageMax(damageMax),
		defence(defence), staminaMax(staminaMax), rarity((int)std::floor(100 / buyGold)) {};

	// Operators

	// Functions

	// Accessors
	inline std::string getName() const { return name; };
	inline std::vector<Role> getRoles() const { return roles; };
	inline int getLevel() const { return level; };
	inline int getBuyGold() const { return buyGold; };
	inline int getSellGold() const { return sellGold; };
	inline int getHpMax()	const { return hpMax; };
	inline int getDamageMax() const { return damageMax; };
	inline int getDefence() const { return defence; };
	inline int getStaminaMax() const { return staminaMax; };
	inline itemType getItemType() const { return itemType; };

	// Modifiers

private:
	// const, the compiler will implicitly delete the copy assignment operator, 
	// as it is not possible to change the value of a const data member.
	std::string name;
	std::vector<Role> roles;	// multiple classes could use it
	itemType itemType;
	int level;
	int buyGold;
	int sellGold;
	int hpMax;
	int damageMax;
	int defence;
	int staminaMax;
	int rarity;
};