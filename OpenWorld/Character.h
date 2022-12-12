#pragma once

#include "Roles.h"
#include<string>
#include <iostream>
#include <algorithm>

class Character
{
public:
	Character(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax, int gold = 0) :
		name(name), hp(hpMax), hpMax(hpMax), damageMin(dmgMin), damageMax(dmgMax), defence(defence), stamina(staminaMax),
		staminaMax(staminaMax), gold(gold) {};

	Character(std::string name, std::vector<int> role, int gold = 0) :
		name(name), hp(role[0]), hpMax(role[0]), damageMin(std::floor(role[1] / 2)), damageMax(role[1]), defence(role[2]), stamina(role[3]),
		staminaMax(role[3]), gold(gold) {};

	virtual ~Character();


	// Operators

	// Functions

	// Accessors
	virtual inline std::string getName() const { return name; };
	virtual inline int getHp() const { return hp; };
	virtual inline int getHpMax() const { return hpMax; };
	virtual inline int getDamageMin() const { return damageMin; };
	virtual inline int getDamageMax() const { return damageMax; };
	virtual inline int getDefence() const { return defence; };
	virtual inline int getGold() const { return gold; };
	virtual inline int getStamina() const { return stamina; };
	virtual inline int getStaminaMax() const { return staminaMax; };

	// Modifiers
	inline void setHp(int hp) { this->hp = hp; };
	inline void setStamina(int stamina) { this->stamina = stamina; };

protected:
	const std::string name;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int defence;
	int stamina;
	int staminaMax;
	int gold;
};

