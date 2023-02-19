#include "Player.h"

Player& Player::operator+=(const Item& item)
{
	this->setHpMax(this->getHpMax() + item.getHpMax());
	this->setHp(std::min(this->getHp(), this->getHpMax()));
	this->setDamage(this->getDamageMax() + item.getDamageMax());
	this->setDefence( this->getDefence() + item.getDefence());

	this->setStaminaMax(this->getStaminaMax() + item.getStaminaMax());
	this->setStamina(std::min(this->getStamina(), this->getStaminaMax()));

	return *this;
}

Player& Player::operator-=(const Item& item)
{
	this->setHpMax(this->getHpMax() - item.getHpMax());
	this->setHp(std::min(this->getHp(), this->getHpMax()));
	this->setDamage(this->getDamageMax() - item.getDamageMax());
	this->setDefence(this->getDefence() - item.getDefence());

	this->setStaminaMax(this->getStaminaMax() - item.getStaminaMax());
	this->setStamina(std::min(this->getStamina(), this->getStaminaMax()));

	return *this;
}

void Player::levelUp()
{
	// The player levels himself up in game as well,is okay to be here
	level++;
	exp = exp - expNext;
	expNext = (int)std::floor(expNext * 1.2 - std::pow(level, 2));

	// Role specific increments:
	setHpMax(hpMax + role.getHpIncr());
	setHp(hpMax);
	setDamage(damageMax + role.getDmgIncr());
	setDefence(defence + role.getDefIncr());
	setStaminaMax(staminaMax + role.getStaminaIncr());
	setStamina(staminaMax);
}

// Take by value, so that both rvalues and lvalues will be accepted. Rvalues are moved twice, lvalues are first copied then moved. 
// If the item object will be only moveable in the future, then taking it as a right value ref is better. (Item&& item)
void Player::addItem(Item item)
{
	Inventory.push_back(std::move(item));
	//Sort items based on name?
}

void Player::useItem(const int& itemPos)
{
	//TODO: temporary consumable
	if (Inventory[itemPos].getItemType() == "consumable") {
		this->hp = this->hpMax;
		return;
	}
	// Check if player can equip item. 
	std::vector<roleName> itemRoles = Inventory[itemPos].getRoles();

	// If role fits
	if (std::find(itemRoles.cbegin(), itemRoles.cend(), role.getRoleName()) != itemRoles.cend()) {

		auto isNotWorn = [&]() -> bool
		{
			auto type = Inventory[itemPos].getItemType();
			int count = (int)std::count_if(Equipment.cbegin(), Equipment.cend(), 
				[&](const auto& equippedItem) {
					return (equippedItem.getItemType() == type);
				});

			// One handed items need special treatment
			if (type == "one handed") {
				// Get count of two handed
				int countTwoHanded = (int)std::count_if(Equipment.cbegin(), Equipment.cend(),
					[&](const auto& equippedItem) {
						return (equippedItem.getItemType() == "two handed");
					});
				if((countTwoHanded == 0) && (count < 2))
					return true;
			}
			else if (type == "two handed") {
				// Get count of one handed
				int countOneHanded = (int)std::count_if(Equipment.cbegin(), Equipment.cend(),
					[&](const auto& equippedItem) {
						return (equippedItem.getItemType() == "one handed");
					});
				if ((countOneHanded == 0) && (count < 1))
					return true;
			}
			else if(count < 1) {
				return true;
			}
			return false;
		};


		// If similar piece is not already worn, maybe switch it automatically later
		if (isNotWorn()){			// Modify player stats
			*this += Inventory[itemPos];

			Equipment.emplace_back(std::move(Inventory[itemPos]));
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

	// Modify player stats
	*this -= Equipment[itemPos];

	Inventory.emplace_back(std::move(Equipment[itemPos]));
	Equipment.erase(Equipment.begin() + itemPos);
}

std::vector<Item>& Player::getInventory()
{
	// Reorder items based on name
	std::sort(Inventory.begin(), Inventory.end(), [](const auto& itemA, const auto& itemB) {
		return itemA.getName() < itemB.getName();
		});

	return Inventory;
}
std::vector<Item>& Player::getEquipment()
{
	// Reorder items based on name
	std::sort(Equipment.begin(), Equipment.end(), [](const auto& itemA, const auto& itemB) {
		return itemA.getName() < itemB.getName();
		});

	return Equipment;
}
