#include "Item.h"

Item::Item(const std::string& name, const std::vector<roleName>& roles, const itemType& type, int hpMax, int damageMax, 
	int defence, int staminaMax) :
	name(name), roles(roles), type(type), hpMax(hpMax), damageMax(damageMax), defence(defence), staminaMax(staminaMax)
{

	static const std::map<itemRarity, int> itemRarityThresholds = {
		{"Mythic", 50},
		{"Legendary", 100},
		{"Epic", 250},
		{"Rare", 500},
		{"Uncommon", 750}
	};

	level = (int)std::floor((hpMax + damageMax + defence + staminaMax) / 2);
	buyGold = hpMax * 2 + damageMax * 3 + defence * 4 + staminaMax;
	sellGold = (int)std::floor(buyGold / 2);
	rarity = (int)std::floor(10000 / (buyGold * buyGold));

	// Start with common, then see where it goes
	this->rarityName = "Common";
	for (const auto& [rarityName, treshold] : itemRarityThresholds) {
		if (rarity <= treshold) {
			this->rarityName = rarityName;
			break;
		}
	}
}
