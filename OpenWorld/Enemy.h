#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int gold, int expDrop) :
		Character(name, hpMax, dmgMin, dmgMax, defence, gold), expDrop(expDrop) {};

	// Operators

	// Functions

	// Accessors
	inline int getExpDrop() const { return expDrop; };

	// Modifiers
	inline void setHp(int hp) { this->hp = hp; };

private:
	int expDrop;

	//std::vector<ItemDrop>
};

