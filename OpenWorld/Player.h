#pragma once
#include "Character.h"
#include <vector>
#include <iostream>

class Player : public Character
{
public:
	Player(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax) :
		Character(name, hpMax, dmgMin, dmgMax, defence, staminaMax), level(1), exp(0), expNext(100) {};

	// Operators

	// Functions

	// Accessors
	inline int getLevel() const { return level; };
	inline int getExp() const { return exp; };
	inline int getExpNext() const { return expNext; };

	// Modifiers
	inline void setGold(int gold) { this->gold = gold; };
	inline void setExp(int exp) { this->exp = exp; };
	inline void setDamage(int damage) { this->damageMax = damage; this->damageMin = std::floor(damage / 2); };
	inline void setDefence(int defence) { this->defence = defence; };

private:
	int level;
	int exp;
	int expNext;

	//std::vector<Item>
};

