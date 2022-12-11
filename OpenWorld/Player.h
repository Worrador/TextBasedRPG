#pragma once
#include "Character.h"

class Player : public Character
{
public:
	// Constructors
	Player(std::string name, bool isMale, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax, Role role, const std::string roleName) :
		Character(name, hpMax, dmgMin, dmgMax, defence, staminaMax), isMale(isMale), level(1), exp(0), expNext(50), role(role), roleName(roleName) {};

	Player(std::string name, bool isMale, Role role, const std::string roleName) :
		Character(name, Roles::getInstance().getRoles()[role]), isMale(isMale), level(1), exp(0), expNext(50), role(role), roleName(roleName) {};

	// Operators

	// Functions
	void levelUp();

	// Accessors
	inline int getLevel() const { return level; };
	inline const std::string getRoleName() const { return roleName; };
	inline int getExp() const { return exp; };
	inline int getExpNext() const { return expNext; };

	// Modifiers
	inline void setGold(int gold) { this->gold = gold; };
	inline void setExp(int exp) { this->exp = exp; };
	inline void setExpNext(int expNext) { this->expNext = expNext; };
	inline void setHpMax(int hpMax) { this->hpMax = hpMax; };
	inline void setStaminaMax(int staminaMax) { this->staminaMax = staminaMax; };
	inline void setDamage(int damage) { this->damageMax = damage; this->damageMin = std::floor(damage / 2); };
	inline void setDefence(int defence) { this->defence = defence; };
	inline void setLevel(int level) { this->level = level; };

private:
	const bool isMale;
	const Role role;
	const std::string roleName;
	int level;
	int exp;
	int expNext;


	//std::vector<Item>
};

