#pragma once
#include "Place.h"
#include "Shop.h"
#include <random>

using settlementSizeType = std::string;

constexpr auto MAXSETTLEMENTSIZE = 7;

class Settlement : public Place
{
public:
	Settlement(const std::string& name, const settlementSizeType& settlementSize, const int& maxConnectionSize);

	// Operators



	// Functions
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " sized settlement)"); };
	inline int getMaxConnectionSize() override { return maxConnectionSize; };

	void setMaxConnectionSize(const int& maxConnectionSize) override { this->maxConnectionSize = maxConnectionSize; };
	// Accessors

	// Modifiers
private:
	settlementSizeType settlementSize;
	int maxConnectionSize = 0;
	std::vector<Shop> settlementShops;

};

