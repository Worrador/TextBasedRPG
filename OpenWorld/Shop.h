#pragma once
#include "Item.h"
#include <string>

using shopType = std::string;

class Shop
{
public:
	// Constructors
	Shop(const shopType& shopName, const std::vector<Item>& shopItems) : shopName(shopName), shopItems(shopItems) {};

	// Operators

	// Functions
	void addRandomItem();

	// Accessors
	inline const std::string& getShopName() const { return shopName; };
	inline std::vector<Item>& getShopItems() { return shopItems; };


private:
	std::string shopName;	// Armor smith, Weapon smith, Potion brewer
	std::vector<Item> shopItems;
};

// Vectors to store items
// Separate shops for armor wepaon and consumables