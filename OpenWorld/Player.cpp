#include "Player.h"

void Player::levelUp()
{
	// The player levels himself up in game as well,is okay to be here
	level++;
	exp = exp - expNext;
	expNext = (int)std::floor(expNext * 1.2 - std::pow(level, 2));

	// Role specific increments:
	auto attrVector = RoleStats::getInstance().getRoleStats()[role];
	setHpMax(hpMax + attrVector[4]);
	setHp(hpMax);
	setDamage(damageMax + attrVector[5]);
	setDefence(defence + attrVector[6]);
	setStaminaMax(staminaMax + attrVector[7]);
	setStamina(staminaMax);
}

void Player::addItem(const Item& item)
{
	Inventory.push_back(item);
	//Sort items based on name?
}
