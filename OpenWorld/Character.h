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
	inline std::string getName() const { return name; };
	inline int getHp() const { return hp; };
	inline int getHpMax() const { return hpMax; };
	inline int getDamageMin() const { return damageMin; };
	inline int getDamageMax() const { return damageMax; };
	inline int getDefence() const { return defence; };
	inline int getGold() const { return gold; };
	inline int getStamina() const { return stamina; };
	inline int getStaminaMax() const { return staminaMax; };

	// Modifiers
	inline void setHp(int hp) { this->hp = hp; };
	inline void setStamina(int stamina) { this->stamina = stamina; };

	inline void setGold(int gold) { this->gold = std::max(gold, 0); };
	inline void setHpMax(int hpMax) { this->hpMax = std::max(hpMax, 1); };
	inline void setStaminaMax(int staminaMax) { this->staminaMax = std::max(staminaMax, 1); };
	inline void setDamage(int damage) { this->damageMax = std::max(damageMax, 1); this->damageMin = std::max((int)std::floor(damage / 2), 0); };
	inline void setDefence(int defence) { this->defence = std::max(defence, 0); };

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

