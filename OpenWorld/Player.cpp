#include "Player.h"

void Player::levelUp()
{
	// The player levels himself up in game as well,is okay to be here
	level++;
	exp = exp - expNext;
	expNext = (int)std::floor(expNext * 1.2 - std::pow(level, 2));

	// Role specific increments:
	auto& attrVector = RoleInfo::getInstance().getRoleStats()[role];
	setHpMax(hpMax + attrVector[4]);
	setHp(hpMax);
	setDamage(damageMax + attrVector[5]);
	setDefence(defence + attrVector[6]);
	setStaminaMax(staminaMax + attrVector[7]);
	setStamina(staminaMax);
}

// Take by value, so that both rvalues and lvalues will be accepted. Rvalues are moved twice, lvalues are first copied then moved. 
// If the item object will be only moveable in the future, then taking it as a right value ref is better. (Item&& item)
void Player::addItem(Item item)
{
	Inventory.push_back(std::move(item));
	//Sort items based on name?
}

//TODO: raneme to useItem
void Player::equipItem(const int& itemPos)
{
	//TODO: temporary consumable
	if (Inventory[itemPos].getItemType() == "consumable") {
		this->hp = this->hpMax;
		return;
	}
	// Check if player can equip item. 
	std::vector<Role> itemRoles = Inventory[itemPos].getRoles();

	// If role fits
	if (std::find(itemRoles.begin(), itemRoles.end(), role) != itemRoles.end()) {

		// If similar piece is not already worn, maybe switch it automatically later
		if ([&]() {for (auto checkPos = 0; checkPos < Equipment.size(); checkPos++) { if(Equipment[checkPos].getItemType() == Inventory[itemPos].getItemType()) return false; } return true; }()) {
			Equipment.push_back(std::move(Inventory[itemPos]));
			Inventory.erase(Inventory.begin() + itemPos);
			return;
		}
	}

	std::cout << "You cannot equip this item." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Player::unequipItem(const int& itemPos)
{
	// Unequip item without question
	Inventory.push_back(std::move(Equipment[itemPos]));
	Equipment.erase(Equipment.begin() + itemPos);
}
