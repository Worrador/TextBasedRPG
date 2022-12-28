#include "Enemy.h"

Enemy& Enemy::operator*=(const int& scaleToLevel)
{
	int scaler = std::max((int)(scaleToLevel * 0.5), 1);
	this->setHpMax(this->getHpMax() * scaler);
	this->setHp(std::min(this->getHp(), this->getHpMax()));
	this->setDamage(this->getDamageMax() * scaler);
	this->setDefence(this->getDefence() * scaler);

	this->setStaminaMax(this->getStaminaMax() * scaler);
	this->setStamina(std::min(this->getStamina(), this->getStaminaMax()));

	this->setExpDrop(getExpDrop() * scaler);
	this->setGold(getGold() * scaler);

	return *this;
}
