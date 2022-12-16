#pragma once
#include "Character.h"

class Player : public Character
{
public:
	// Constructors
	Player(const std::string& name, bool isMale, int hpMax, int dmgMin, int dmgMax, int defence, int staminaMax, const Role& role, const std::string& roleName) :
		Character(name, hpMax, dmgMin, dmgMax, defence, staminaMax), isMale(isMale), level(1), exp(0), expNext(50), role(role), roleName(roleName) {};

	//TODO: map or fn that maps role to rolename
	Player(const std::string& name, bool isMale, const Role& role, const std::string& roleName) :
		Character(name, RoleStats::getInstance().getRoleStats()[role]), isMale(isMale), level(1), exp(0), expNext(50), role(role), roleName(roleName) {};

	// Operators

	// Functions
	void levelUp();
	void addItem( const Item& item );
	void equipItem( const Item& item );
	void unequipItem( const Item& item );

	// Accessors
	inline const int & getLevel() const { return level; };
	inline const std::string& getRoleName() const { return roleName; };
	inline const int& getExp() const { return exp; };
	inline const int& getExpNext() const { return expNext; };
	inline const std::vector<Item>& getInventory() const { return Inventory; };

	// Stat Modifiers
	inline void setGold(int gold) { this->gold = std::max(gold, 0); };
	inline void setExp(int exp) { this->exp = exp; };
	inline void setExpNext(int expNext) { this->expNext = expNext; };
	inline void setHpMax(int hpMax) { this->hpMax = std::max(hpMax, 1); };
	inline void setStaminaMax(int staminaMax) { this->staminaMax = std::max(staminaMax, 1); };
	inline void setDamage(int damage) { this->damageMax = std::max(damageMax, 1); this->damageMin = std::max((int)std::floor(damage / 2), 0); };
	inline void setDefence(int defence) { this->defence = std::max(defence, 0); };
	inline void setLevel(int level) { this->level = level; };

private:
	const bool isMale;
	const Role role;
	const std::string roleName;
	int level;
	int exp;
	int expNext;
	// Inventory
	std::vector<Item> Inventory;

};

