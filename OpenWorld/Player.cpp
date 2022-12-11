#include "Player.h"

void Player::levelUp()
{
	level++;
	exp = exp - expNext;
	expNext = std::floor(expNext * 1.2 - std::pow(level, 2));

	// Role specific increments:
	auto attrVector = Roles::getInstance().getRoles()[role];
	setHpMax(hpMax + attrVector[4]);
	setHp(hpMax);
	setDamage(damageMax + attrVector[5]);
	setDefence(defence + attrVector[6]);
	setStaminaMax(staminaMax + attrVector[7]);
	setStamina(staminaMax);
}
