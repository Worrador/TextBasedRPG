#pragma once
#include "Character.h"
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds

class Player : public Character
{
public:
	// Constructors
	Player(const std::string& name, bool isMale, int hpMax, int dmgMax, int dmgMin, int defence, int staminaMax, const Role& role) :
		Character(name, hpMax, dmgMax, dmgMin, defence, staminaMax), isMale(isMale), level(1), exp(0), expNext(50), role(role) {};

	Player(const std::string& name, bool isMale, const Role& role) :
		role(role), isMale(isMale), 
		Character(name, role.getStartingHpMax(), role.getStartingDmgMax(), (int)std::floor(role.getStartingDmgMax() / 2), role.getStartingDef(), role.getStartingStaminaMax()) {};

	// Operators
	Player& operator+=(const Item& item);
	Player& operator-=(const Item& item);

	// Functions
	void levelUp();
	void addItem( Item item );
	void equipItem( const int& item );
	void unequipItem( const int& item );

	// Accessors
	inline const int & getLevel() const { return level; };
	inline const Role& getRole() const { return role; };
	inline const roleName& getRoleName() const { return role.getRoleName(); };
	inline const int& getExp() const { return exp; };
	inline const int& getExpNext() const { return expNext; };
	inline const std::vector<Item>& getInventory() const { return Inventory; };
	inline const std::vector<Item>& getEquipment() const { return Equipment; };

	// Stat Modifiers
	inline void setExp(int exp) { this->exp = exp; };
	inline void setExpNext(int expNext) { this->expNext = expNext; };
	inline void setLevel(int level) { this->level = level; };


private:
	const bool isMale;
	const Role role;
	int level = 1;
	int exp = 0;
	int expNext = 50;
	// Inventory
	std::vector<Item> Equipment;
	std::vector<Item> Inventory;

};

