#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(const std::string& name, int hpMax, int dmgMax, int defence, int staminaMax, int aggressivity) :
		Character(name, hpMax, dmgMax, (int)std::floor(dmgMax / 2), defence, staminaMax, (int)std::floor(std::max(dmgMax, hpMax) / 5)), expDrop(dmgMax + hpMax),
		aggressivity(aggressivity), rarity((int)std::floor(10000 / (hpMax + defence + dmgMax) * (1 + staminaMax / staminaMax))) {};

	Enemy (const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(const Enemy&) = default;
	Enemy& operator=(Enemy&&) = default;

	// Operators
	Enemy& operator*(const int& scaleToLevel);

	// Functions

	// Accessors
	inline int getExpDrop() const { return expDrop; };
	inline int getAggressivity() const { return aggressivity; };
	inline int getRarity() const { return rarity; };

	// Modifiers
	inline void setExpDrop(int newExpDrop) { expDrop = newExpDrop; };

private:
	int expDrop;
	int aggressivity;

	//TODO: rarity function that can be used for items and enemies maybe even places too
	int rarity;

	//std::vector<ItemDrop>
};

