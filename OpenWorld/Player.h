#pragma once
#include "Character.h"
#include <vector>

class Player : public Character
{
public:
	Player(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int stamina) : 
		Character(name, hpMax, dmgMin, dmgMax, defence), level(0), exp(0), expNext(100), stamina(stamina) {};

	// Operators

	// Functions

	// Accessors
	inline int getLevel() const { return level; };

	// Modifiers

private:
	int level;
	int exp;
	int expNext;
	int stamina;

	//std::vector<Item>
};

