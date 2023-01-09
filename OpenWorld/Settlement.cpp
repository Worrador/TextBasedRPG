#include "Settlement.h"

Settlement::Settlement(const std::string& name, const settlementSizeType& settlementSize, const int& maxConnectionSize)
	: Place(name, ""), settlementSize(settlementSize)
{
	// Error handling in case something goes wrong, settlement size can only be MAXSETTLEMENTSIZE at max
	this->maxConnectionSize = (maxConnectionSize > MAXSETTLEMENTSIZE) ? MAXSETTLEMENTSIZE : maxConnectionSize;

	// Possible types of shops
	std::vector<shopType> shopTypes = {"Armor smith", "Weapon smith", "Potion brewer"};
	
	// Shuffle shoptypes then resize according to settlement size then sort it
	std::mt19937 rng;
	std::shuffle(shopTypes.begin(), shopTypes.end(), rng);
	shopTypes.resize((int)(maxConnectionSize / 2));
	std::sort(shopTypes.begin(), shopTypes.end());

	// Add shops accordingly to this settlement
	for (auto& shopType : shopTypes)
	{	
		// Create items for the given shoptype
		std::vector<Item> shopItems;

		settlementShops.emplace_back(shopType, std::move(shopItems));
	}

}
