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
	void equipItem( const int& item );
	void unequipItem( const int& item );

	// Accessors
	inline const int & getLevel() const { return level; };
	inline const Role& getRole() const { return role; };
	inline const roleName& getRoleName() const { return role.getRoleName(); };
	inline const int& getExp() const { return exp; };
	inline const int& getExpNext() const { return expNext; };
	inline std::vector<Item>& getInventory() { 
		// Reorder items based on name
		std::sort(Inventory.begin(), Inventory.end(), [](const auto& itemA, const auto& itemB) {
			return itemA.getName() < itemB.getName();
			});

		return Inventory; 
	};
	inline const std::vector<Item>& getEquipment() { 
		// Reorder items based on name
		std::sort(Equipment.begin(), Equipment.end(), [](const auto& itemA, const auto& itemB) {
			return itemA.getName() < itemB.getName();
			});

		return Equipment; 
	};	
	inline void addToKnownSettlements(const int& settlementId) { knownSettlements.emplace_back(settlementId); map.emplace_back(settlementId); };
	inline void addToKnownTerrains(const int& terrainId) { map.emplace_back(terrainId); };

	// Stat Modifiers
	inline void setExp(int exp) { this->exp = exp; };
	inline void setExpNext(int expNext) { this->expNext = expNext; };
	inline void setLevel(int level) { this->level = level; };
	inline const playerMap& getMap() const { return map; };
	inline const playerMap& getKnownSettlements() const { return knownSettlements; };


private:

	inline void addToMap(const int& discoveredId) { map.emplace_back(discoveredId); };

	const Role role;
	const bool isMale;
	int level = 1;
	int exp = 0;
	int expNext = 50;
	// Inventory
	std::vector<Item> Equipment;
	std::vector<Item> Inventory;
	playerMap map;
	playerMap knownSettlements;
};

