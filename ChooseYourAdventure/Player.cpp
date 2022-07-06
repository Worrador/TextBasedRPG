#include "Player.h"

int Player::get_hp()
{
	return this->hp;
}

void Player::update_hp(int dmg)
{
	this->hp -= dmg;
}
