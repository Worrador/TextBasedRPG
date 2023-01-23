#include "Enemy.h"

Enemy::Enemy(const std::string& name, int hpMax, int dmgMax, int defence, int staminaMax, int aggressivity) :
	Character(name, hpMax, dmgMax, (int)std::floor(dmgMax / 2), defence, staminaMax, (int)std::floor(std::max(dmgMax, hpMax) / 5)), expDrop(dmgMax + hpMax),
	aggressivity(aggressivity)
{
	rarity = ((int)std::floor(10000 / (hpMax + defence + dmgMax) * (1 + staminaMax / staminaMax)));
	// Start with common, then see where it goes
	this->rarityName = RARITY_LEVEL_1;
	for (const auto& [rarityName, treshold] : enemyRarityThresholds) {
		if (rarity <= treshold) {
			this->rarityName = rarityName;
			break;
		}
	}
	lootItems.emplace_back(getRandomItem(this->rarityName));
}

Enemy& Enemy::operator*(const int& scaleToLevel)
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
	this->rarity = this->rarity * scaler;
	this->lootItems.clear();
	lootItems.emplace_back(getRandomItem(this->rarityName));

	return *this;
}

Item Enemy::getRandomItem(const itemRarity& rarityName) {

	std::vector<Item> parsedItems = ItemParser::getInstance().getParsedArmors();
	std::vector<Item> parsedItems2 = ItemParser::getInstance().getParsedWeapons();
	parsedItems.insert(parsedItems.cbegin() + parsedItems.size() - 1, parsedItems2.begin(), parsedItems2.end());

	// shuffle parseditems vector while we do not get an item that is good in rarity
	int randomItemNum;
	do {
		randomItemNum = getRandomBetween(0, (int)parsedItems.size() - 1);
	} while (parsedItems[randomItemNum].getRarityName() != rarityName);

	return parsedItems[randomItemNum];
}