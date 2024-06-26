#pragma once
#include "Place.h"
#include "Shop.h"
#include "ItemParser.h"

using settlementSizeType = std::string;

class Settlement : public Place
{
public:
	Settlement(const std::string& name, const settlementSizeType& settlementSize, const int& maxConnectionSize);

	void addRandomShopItem(std::vector<Item>& shopItems, shopType type);

	// Operators

	// Functions
	inline const std::vector<std::string>& getEnemiesDay() const override { return enemiesOutsideDay; };
	inline const std::vector<std::string>& getEnemiesNight() const override { return enemiesOutsideNight; };
	inline const int& getEnemiesDayRaritySum() const override { return enemiesOutsideDayRaritySum; }
	inline const int& getEnemiesNightRaritySum() const override { return enemiesOutsideNightRaritySum; }
	inline const std::vector<std::pair<std::string, int>>& getRestOptions() const override { return restOptions; }
	const bool isSettlement() const override { return true; }

	// Accessors
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " sized settlement)"); };
	inline int getMaxConnectionSize() override { return maxConnectionSize; };
	const std::vector<std::string> getMenuOptions() const override;
	Shop& getShop(shopType shop);

	// Modifiers
	void setMaxConnectionSize(const int maxConnectionSize) override { this->maxConnectionSize = maxConnectionSize; };

private:
	settlementSizeType settlementSize;
	int maxConnectionSize{};
	std::vector<Shop> settlementShops;
	std::vector<std::pair<std::string, int>> restOptions;


	std::vector<std::string> enemiesOutsideDay = {};
	std::vector<std::string> enemiesOutsideNight = {};
	int enemiesOutsideDayRaritySum{};
	int enemiesOutsideNightRaritySum{};
};

