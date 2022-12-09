#pragma once

#include<string>

class Character
{
public:
	Character(std::string name, int hpMax, int dmgMin, int dmgMax, int defence) : 
		name(name), hp(hpMax), hpMax(hpMax), damageMin(dmgMin), damageMax(dmgMax), defence(defence) {};
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

	// Modifiers

private:
	std::string name;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int defence;
};

