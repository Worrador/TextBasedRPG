#pragma once
#include "Item.h"

class Character
{
public:
	Character(const std::string& name, const int& hpMax, const int& dmgMax, const int& dmgMin, const int& defence, const int& staminaMax, const int& gold = 0) :
		name(name), hp(hpMax), hpMax(hpMax), damageMax(dmgMax), damageMin(dmgMin), defence(defence), stamina(staminaMax),
		staminaMax(staminaMax), gold(gold) {};

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

