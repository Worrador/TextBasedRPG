#pragma once
#include "Roles.h"
#include <string>

class Item
{
public:
	Item(const std::string& name, const Role& role, int level, int buyGold, int hpMax, int damageMax, int defence, int staminaMax) :
		name(name), role(role), level(level), buyGold(buyGold), sellGold(buyGold), hpMax(hpMax), damageMax(damageMax), defence(defence), 
		staminaMax(staminaMax) {};

	// Operators

	// Functions

	// Accessors
	inline const std::string getName() const { return name; };
	inline const Role getRole() const { return role; };
	inline const int getLevel() const { return level; };
	inline const int getBuyGold() const { return buyGold; };
	inline const int getSellGold() const { return sellGold; };
	inline const int getHpMax()	const { return hpMax; };
	inline const int getDamageMax() const { return damageMax; };
	inline const int getDefence() const { return defence; };
	inline const int getStaminaMax() const { return staminaMax; };

	// Modifiers

private:
	const std::string name;
	const Role role;
	const int level;
	const int buyGold;
	const int sellGold;
	const int hpMax;
	const int damageMax;
	const int defence;
	const int staminaMax;
};