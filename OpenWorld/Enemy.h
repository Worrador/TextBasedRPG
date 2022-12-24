#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(const std::string& name, int hpMax, int dmgMax, int dmgMin, int defence, int staminaMax, int gold, int expDrop) :
		Character(name, hpMax, dmgMax, dmgMin, defence, staminaMax, gold), expDrop(expDrop) {};

	// Operators

	// Functions

	// Accessors
	inline int getExpDrop() const { return expDrop; };

	// Modifiers

private:
	int expDrop;

	//std::vector<ItemDrop>
};

