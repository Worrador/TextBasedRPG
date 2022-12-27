#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(const std::string& name, int hpMax, int dmgMax, int dmgMin, int defence, int staminaMax, int gold, int expDrop) :
		Character(name, hpMax, dmgMax, dmgMin, defence, staminaMax, gold), expDrop(expDrop) {};

	Enemy(const std::string& name, int hpMax, int dmgMax, int dmgMin, int defence, int staminaMax) :
		Character(name, hpMax, dmgMax, dmgMin, defence, staminaMax, std::max(dmgMax, hpMax)), expDrop(dmgMax + hpMax) {};

	// Operators
	Enemy& operator*=(const int& scaleToLevel);

	// Functions

	// Accessors
	inline int getExpDrop() const { return expDrop; };

	// Modifiers
	inline int setExpDrop(int newExpDrop) { expDrop = newExpDrop; };

private:
	int expDrop;

	//std::vector<ItemDrop>
};

