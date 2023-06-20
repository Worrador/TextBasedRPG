#include "Player.h"

Player& Player::operator+=(const Item& item)
{
	this->setHpMax(this->getRawHpMax() + item.getHpMax());
	this->setHp(std::min(this->getHp(), this->getHpMax()));
	this->setDamage(this->getRawDamageMax() + item.getDamageMax());
	this->setDefence( this->getRawDefence() + item.getDefence());

	this->setStaminaMax(this->getRawStaminaMax() + item.getStaminaMax());
	this->setStamina(std::min(this->getStamina(), this->getStaminaMax()));

	return *this;
}

Player& Player::operator-=(const Item& item)
{
	this->setHpMax(this->getRawHpMax() - item.getHpMax());
	this->setHp(std::min(this->getHp(), this->getHpMax()));
	this->setDamage(this->getRawDamageMax() - item.getDamageMax());
	this->setDefence(this->getRawDefence() - item.getDefence());

	this->setStaminaMax(this->getRawStaminaMax() - item.getStaminaMax());
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

// LESSON: Take by value, so that both rvalues and lvalues will be accepted. Rvalues are moved twice!!, lvalues are first copied then moved. 
// If the item object will be only moveable in the future, then taking it as a right value ref is better. (Item&& item)
void Player::addItem(Item item)
{
	Inventory.push_back(std::move(item));

	// Reorder items based on name
	std::sort(Inventory.begin(), Inventory.end(), [](const auto& itemA, const auto& itemB) {
		return itemA.getName() < itemB.getName();
		});
}

void Player::useItem(const int itemPos)
{
	//TODO: temporary consumable
	const auto& itemtype = Inventory[itemPos].getItemType();
	if (itemtype == "healing") {
		this->setHp(std::min(this->getHp() + Inventory[itemPos].getHpMax(), this->getHpMax()));
		
		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	else if (itemtype == "stamina regeneration") {
		this->setStamina(std::min(this->getStamina() + Inventory[itemPos].getStaminaMax(), this->getStaminaMax()));
		
		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	else if (itemtype == "strength") {
		setBuffDamageMax(getBuffDamageMax() + Inventory[itemPos].getDamageMax());

		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	else if (itemtype == "defence") {
		setBuffDefence(getBuffDefence() + Inventory[itemPos].getDefence());

		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	else if (itemtype == "health") {
		setBuffHpMax(getBuffHpMax() + Inventory[itemPos].getHpMax());

		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	else if (itemtype == "stamina") {
		setBuffStaminaMax(getBuffStaminaMax() + Inventory[itemPos].getStaminaMax());

		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	else if (itemtype == "food") {
		this->setHp(std::min(this->getHp() + Inventory[itemPos].getHpMax(), this->getHpMax()));
		this->setStamina(std::min(this->getStamina() + Inventory[itemPos].getStaminaMax(), this->getStaminaMax()));

		setBuffDamageMax(getBuffDamageMax() + Inventory[itemPos].getDamageMax());
		setBuffDefence(getBuffDefence() + Inventory[itemPos].getDefence());

		Inventory.erase(Inventory.begin() + itemPos);
		return;
	}
	//TODO: different stats for consumables
	
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
			// Reorder items based on name
			std::sort(Equipment.begin(), Equipment.end(), [](const auto& itemA, const auto& itemB) {
				return itemA.getName() < itemB.getName();
				});

			Inventory.erase(Inventory.begin() + itemPos);

			return;
		}
	}

	std::cout << "You cannot equip this item." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Player::unequipItem(const int itemPos)
{
	// Unequip item without question

	// Modify player stats
	*this -= Equipment[itemPos];

	Inventory.emplace_back(std::move(Equipment[itemPos]));
	// Reorder items based on name
	std::sort(Inventory.begin(), Inventory.end(), [](const auto& itemA, const auto& itemB) {
		return itemA.getName() < itemB.getName();
		});

	Equipment.erase(Equipment.begin() + itemPos);
}