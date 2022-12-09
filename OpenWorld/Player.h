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
	inline int setStaminaToMax() { stamina = staminaMax; };

private:
	int level;
	int exp;
	int expNext;
	int stamina;
	int staminaMax;

	//std::vector<Item>
};

