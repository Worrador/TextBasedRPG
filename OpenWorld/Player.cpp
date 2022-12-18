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
