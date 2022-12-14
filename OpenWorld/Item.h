#pragma once
#include "RoleStats.h"
#include <string>
#include <algorithm>
#include <iostream>

enum class itemType {
	oneHanded = 0,
	twoHanded,
	headPiece,
	handPiece,
	chestPiece,
	legPiece,
	shoes,
	potion
};

class Item
{
public:
	Item(const std::string& name, const std::vector<Role>& roles, const itemType& itemType, int hpMax, int damageMax, int defence, int staminaMax) :
		name(name), roles(roles), itemType(itemType),level((int)std::floor((hpMax + damageMax + defence + staminaMax) / 2)), hpMax(hpMax),
		buyGold(hpMax * 2 + damageMax * 2 + defence * 3 + staminaMax), sellGold((int)std::floor(buyGold / 2)), damageMax(damageMax),
		defence(defence), staminaMax(staminaMax) {};

	// Operators

	// Functions

	// Accessors
	inline const std::string getName() const { return name; };
	inline const std::vector<Role> getRole() const { return roles; };
	inline const int getLevel() const { return level; };
	inline const int getBuyGold() const { return buyGold; };
	inline const int getSellGold() const { return sellGold; };
	inline const int getHpMax()	const { return hpMax; };
	inline const int getDamageMax() const { return damageMax; };
	inline const int getDefence() const { return defence; };
	inline const int getStaminaMax() const { return staminaMax; };

	// Modifiers
	inline void equip() { this->isEquipped = true; };
	inline void unequip() { this->isEquipped = false; };

private:
	const std::string name;
	const std::vector<Role> roles;	// multiple classes could use it
	const itemType itemType;
	const int level;
	const int buyGold;
	const int sellGold;
	const int hpMax;
	const int damageMax;
	const int defence;
	const int staminaMax;

	bool isEquipped = false;
};