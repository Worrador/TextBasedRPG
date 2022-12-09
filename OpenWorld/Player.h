#pragma once
#include "Character.h"
#include <vector>

class Player : public Character
{
public:
	Player(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax) :
		Character(name, hpMax, dmgMin, dmgMax, defence), level(1), exp(0), expNext(100), stamina(staminaMax), staminaMax(staminaMax) {};

	// Operators

	// Functions

	// Accessors
	inline int getLevel() const { return level; };
	inline int getExp() const { return exp; };
	inline int getExpNext() const { return expNext; };
	inline int getStamina() const { return stamina; };
	inline int getStaminaMax() const { return staminaMax; };

	// Modifiers
	inline void setStamina(int stamina) { this->stamina = stamina; };
	inline void setHp(int hp) { this->hp = hp; };
	inline void setGold(int gold) { this->gold = gold; };
	inline void setExp(int exp) { this->exp = exp; };

private:
	int level;
	int exp;
	int expNext;
	int stamina;
	int staminaMax;

	//std::vector<Item>
};

