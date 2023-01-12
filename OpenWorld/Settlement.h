#pragma once
#include "Place.h"
#include "Shop.h"
#include "ItemParser.h"
#include <random>

using settlementSizeType = std::string;

constexpr auto MAXSETTLEMENTSIZE = 7;

class Settlement : public Place
{
public:
	int getRandomBetween(int lower, int higher);
	Settlement(const std::string& name, const settlementSizeType& settlementSize, const int& maxConnectionSize);

	void addRandomShopItem(std::vector<Item>& shopItems, shopType type);

	// Operators

	// Functions

	// Accessors
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " sized settlement)"); };
	inline int getMaxConnectionSize() override { return maxConnectionSize; };
	const std::vector<std::string> getMenuOptions() const override;
	Shop& getShop(shopType shop);

	// Modifiers
	void setMaxConnectionSize(const int& maxConnectionSize) override { this->maxConnectionSize = maxConnectionSize; };

private:
	settlementSizeType settlementSize;
	int maxConnectionSize = 0;
	std::vector<Shop> settlementShops;
	std::mt19937 randomNumberGenerator;

};

