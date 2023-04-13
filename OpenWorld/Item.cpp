#include "Item.h"

Item::Item(const std::string& name, const std::vector<roleName>& roles, const itemType& type, int hpMax, int damageMax, 
	int defence, int staminaMax) :
	name(name), roles(roles), type(type), hpMax(hpMax), damageMax(damageMax), defence(defence), staminaMax(staminaMax)
{

	level = (int)std::floor((hpMax + damageMax + defence + staminaMax) / 2);
	buyGold = hpMax * 2 + damageMax * 3 + defence * 5 + staminaMax;
	sellGold = (int)std::floor(buyGold / 2);
	rarity = (int)std::floor(10000 / (buyGold * buyGold));

	// Start with common, then see where it goes
	this->rarityName = RARITY_LEVEL_1;
	for (const auto& [rarityName, treshold] : itemRarityThresholds) {
		if (rarity <= treshold) {
			this->rarityName = rarityName;
			break;
		}
	}
}

Item& Item::operator=(const Item& other) noexcept
{
	if (this != &other) {
		// LESSON: we should have our copy constructor ideally
		// By implementing the copy-and-swap idiom we get less code repetition as in the copy assignment we call 
		// the copy constructor. We also get strong exception safety. Is there a catch?
		// You might get a performance hit.After all, we have to make an extra allocation in the copy assignment 
		// where we create the temporary.

		Item temp(other);
		swap(*this, temp);
	}
	return *this;
}

void swap(Item& lhs, Item& rhs) noexcept
{
	using std::swap;
	swap(lhs.name, rhs.name);
	swap(lhs.roles, rhs.roles);
	swap(lhs.type, rhs.type);
	swap(lhs.level, rhs.level);
	swap(lhs.sellGold, rhs.sellGold);
	swap(lhs.hpMax, rhs.hpMax);
	swap(lhs.damageMax, rhs.damageMax);
	swap(lhs.defence, rhs.defence);
	swap(lhs.staminaMax, rhs.staminaMax);
	swap(lhs.buyGold, rhs.buyGold);
	swap(lhs.rarity, rhs.rarity);
	swap(lhs.rarityName, rhs.rarityName);
}