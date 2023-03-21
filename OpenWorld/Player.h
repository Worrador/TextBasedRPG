#pragma once
#include "Character.h"
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds



using playerMap = std::vector<int>;

class Player : public Character
{
public:
	// Constructors
	Player(const std::string& name, bool isMale, int hpMax, int dmgMax, int dmgMin, int defence, int staminaMax, const Role& role) :
		Character(name, hpMax, dmgMax, dmgMin, defence, staminaMax), isMale(isMale), level(1), exp(0), role(role), expNext(50) {};

	Player(const std::string& name, bool isMale, const Role& role) :
		Character(name, role.getStartingHpMax(), role.getStartingDmgMax(), (int)std::floor(role.getStartingDmgMax() / 2), role.getStartingDef(), role.getStartingStaminaMax()), 
		role(role), isMale(isMale){};
	// Operators
	Player& operator+=(const Item& item);
	Player& operator-=(const Item& item);

	// Functions
	void levelUp();
	void addItem( Item item );
	void useItem( const int& item );
	void unequipItem( const int& item );

	// Accessors
	inline const int & getLevel() const { return level; };
	inline const Role& getRole() const { return role; };
	inline const roleName& getRoleName() const { return role.getRoleName(); };
	inline const int& getExp() const { return exp; };
	inline const int& getExpNext() const { return expNext; };

	inline const int& getBuffHpMax() const { return buff_hpMax; };
	inline const int& getBuffDamageMax() const { return buff_damageMax; };
	inline const int& getBuffDefence() const { return buff_defence; };
	inline const int& getBuffStaminaMax() const { return buff_staminaMax; };

	inline const std::vector<Item>& getInventory() const { return Inventory; };
	inline const std::vector<Item>& getEquipment() const { return Equipment; };

	inline const playerMap& getMap() const { return map; };
	inline const playerMap& getKnownSettlements() const { return knownSettlements; };

	// Stat Modifiers
	inline void setExp(int exp) { this->exp = exp; };
	inline void setExpNext(int expNext) { this->expNext = expNext; };
	inline void setLevel(int level) { this->level = level; };

	inline void addToKnownSettlements(const int& settlementId) { knownSettlements.emplace_back(settlementId); map.emplace_back(settlementId); };
	inline void addToKnownTerrains(const int& terrainId) { map.emplace_back(terrainId); };

	inline void setBuffHpMax(int stat) { buff_hpMax = stat; };
	inline void setBuffDamageMax(int stat) { buff_damageMax = stat; };
	inline void setBuffDefence(int stat) { buff_defence = stat; };
	inline void setBuffStaminaMax(int stat) { buff_staminaMax = stat; };

	// Provide way for sell menu to modify inventory, which is always returned as const ref by the getter
	inline void popFromInv(int pos) { Inventory.erase(Inventory.cbegin() + pos); };


private:

	inline void addToMap(const int& discoveredId) { map.emplace_back(discoveredId); };

	const Role role;
	const bool isMale;
	int level = 1;
	int exp = 0;
	int expNext = 50;

	int buff_hpMax = 0;
	int buff_damageMax = 0;
	int buff_defence = 0;
	int buff_staminaMax = 0;

	// Inventory
	std::vector<Item> Equipment;
	std::vector<Item> Inventory;
	playerMap map;
	playerMap knownSettlements;
};

