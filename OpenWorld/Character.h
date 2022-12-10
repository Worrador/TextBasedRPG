#pragma once

#include<string>

class Character
{
public:
	//TODO: utánna járni a sokconstrucotor eloadásnak
	Character(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax, int gold) :
		name(name), hp(hpMax), hpMax(hpMax), damageMin(dmgMin), damageMax(dmgMax), defence(defence), stamina(staminaMax), 
		staminaMax(staminaMax), gold(gold) {};

	Character(std::string name, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax) :
		name(name), hp(hpMax), hpMax(hpMax), damageMin(dmgMin), damageMax(dmgMax), defence(defence), stamina(staminaMax),
		staminaMax(staminaMax), gold(0) {};

	~Character();


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
	std::string name;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int defence;
	int stamina;
	int staminaMax;
	int gold;
};

