#include "Player.h"

void Player::levelUp()
{
	level++;
	exp = exp - expNext;
	expNext = expNext * 2 - std::pow(level, 2);

}
