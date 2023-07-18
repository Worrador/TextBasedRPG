#pragma once
#include "Character.h"
#include "Quest.h"
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
	void addQuest( Quest quest);
	void useItem( int item );
	void unequipItem( int item );

	// Accessors
	int getHpMax() const override { return hpMax + buff_hpMax; };
	int getDamageMin() const override { return getDamageMax() / 2; };
	int getDamageMax() const override { return damageMax + buff_damageMax; };
	int getDefence() const override { return defence + buff_defence; };
	int getStaminaMax() const override { return staminaMax + buff_staminaMax; };

	int getRawHpMax() const { return hpMax; };
	int getRawDamageMin() const { return getDamageMax() / 2; };
	int getRawDamageMax() const { return damageMax; };
	int getRawDefence() const { return defence; };
	int getRawStaminaMax() const { return staminaMax; };


	const int & getLevel() const { return level; };
	const Role& getRole() const { return role; };
	const roleName& getRoleName() const { return role.getRoleName(); };
	const int& getExp() const { return exp; };
	const int& getExpNext() const { return expNext; };

	const int& getBuffHpMax() const { return buff_hpMax; };
	const int& getBuffDamageMax() const { return buff_damageMax; };
	const int& getBuffDefence() const { return buff_defence; };
	const int& getBuffStaminaMax() const { return buff_staminaMax; };

	std::vector<Item>& getInventory() { return Inventory; };
	std::vector<Item>& getEquipment() { return Equipment; };

	const std::vector<Item>& getInventory() const { return Inventory; };
	const std::vector<Item>& getEquipment() const { return Equipment; };

	const playerMap& getMap() const { return map; };
	const playerMap& getKnownSettlements() const { return knownSettlements; };

	// Stat Modifiers
	void setExp(const int exp) { this->exp = exp; };
	void setExpNext(const int expNext) { this->expNext = expNext; };
	void setLevel(const int level) { this->level = level; };

	void addToKnownSettlements(const int settlementId) { knownSettlements.emplace_back(settlementId); map.emplace_back(settlementId); };
	void addToKnownTerrains(const int terrainId) { map.emplace_back(terrainId); };

	void setBuffHpMax(const int stat) { buff_hpMax = stat; };
	void setBuffDamageMax(const int stat) { buff_damageMax = stat; };
	void setBuffDefence(const int stat) { buff_defence = stat; };
	void setBuffStaminaMax(const int stat) { buff_staminaMax = stat; };

	// Provide way for sell menu to modify inventory, which is always returned as const ref by the getter
	void popFromInv(const int pos) { Inventory.erase(Inventory.cbegin() + pos); };

	const std::vector<Quest>& getQuests() const { return quests; };


private:

	void addToMap(const int& discoveredId) { map.emplace_back(discoveredId); };

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
	std::vector<Quest> quests;
};

