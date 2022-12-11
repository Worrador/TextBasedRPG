#pragma once
#include "Character.h"
#include <vector>
#include <iostream>

class Player : public Character
{
public:
	Player(std::string name, bool isMale, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax) :
		Character(name, hpMax, dmgMin, dmgMax, defence, staminaMax), isMale(isMale), level(1), exp(0), expNext(5) {};

	// Operators

	// Functions

	// Accessors
	inline int getLevel() const { return level; };
	inline int getExp() const { return exp; };
	inline int getExpNext() const { return expNext; };

	// Modifiers
	inline void setGold(int gold) { this->gold = gold; };
	inline void setExp(int exp) { this->exp = exp; };
	inline void setExpNext(int expNext) { this->expNext = expNext; };
	inline void setDamage(int damage) { this->damageMax = damage; this->damageMin = std::floor(damage / 2); };
	inline void setDefence(int defence) { this->defence = defence; };
	inline void setLevel(int level) { this->level = level; };

private:
	bool isMale;
	int level;
	int exp;
	int expNext;

	//std::vector<Item>
};

