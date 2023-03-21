#pragma once
#include "Item.h"
#include <string>

using shopType = std::string;

constexpr auto SHOP_TYPE_ARMOR = "Armor smith";
constexpr auto SHOP_TYPE_WEAPON = "Weapon smith";
constexpr auto SHOP_TYPE_CONSUMABLE = "General goods merchant";
constexpr auto NUMBER_OF_SHOP_TYPES = 3;

class Shop
{
public:
	// Constructors
	Shop(const shopType& shopName, const std::vector<Item>& shopItems) : shopName(shopName), shopItems(shopItems) {};

	// Operators

	// Functions

	// Accessors
	inline const std::string& getShopName() const { return shopName; };
	inline std::vector<Item>& getShopItems() { 
		// Reorder items based on name
		std::sort(shopItems.begin(), shopItems.end(), [](const auto& itemA, const auto& itemB) {
			return itemA.getName() < itemB.getName();
			});

		return shopItems; 
	};


private:
	shopType shopName;	// Armor smith, Weapon smith, Potion brewer
	std::vector<Item> shopItems;
};