#pragma once
#include "Character.h"

extern std::map<Role, std::vector<int>> Roles;

class Enemy : public Character
{
public:
	Enemy(const std::string& name, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax, int gold, int expDrop) :
		Character(name, hpMax, dmgMin, dmgMax, defence, staminaMax, gold), expDrop(expDrop) {};

	// Operators

	// Functions

	// Accessors
	inline int getExpDrop() const { return expDrop; };

	// Modifiers

private:
	int expDrop;

	//std::vector<ItemDrop>
};

