#include "Settlement.h"

Settlement::Settlement(const std::string& name, const settlementSizeType& settlementSize, const int& maxConnectionSize)
	: Place(name, ""), settlementSize(settlementSize)
{
	// Error handling in case something goes wrong, settlement size can only be MAXSETTLEMENTSIZE at max
	this->maxConnectionSize = (maxConnectionSize > MAX_CONNECTION_SIZE_SETTLEMENT) ? MAX_CONNECTION_SIZE_SETTLEMENT : maxConnectionSize;

	// Possible types of shops
	std::vector<shopType> shopTypes = { SHOP_TYPE_ARMOR, SHOP_TYPE_WEAPON, SHOP_TYPE_CONSUMABLE };
	
	// Shuffle shoptypes then resize according to settlement size then sort it
	std::shuffle(shopTypes.begin(), shopTypes.end(), randomNumberGenerator);
	shopTypes.resize((int)(maxConnectionSize / 2));
	std::sort(shopTypes.begin(), shopTypes.end());

	// Add shops accordingly to this settlement
	for (auto& shopType : shopTypes)
	{	
		// Create items for the given shoptype
		std::vector<Item> shopItems;
		for (auto count = 0; count < maxConnectionSize; count++) {
			addRandomShopItem(shopItems, shopType);
		}
		settlementShops.emplace_back(shopType, std::move(shopItems));
	}

	// Add rest options based on Settlement size
	restOptions.emplace_back("Sleep outside the settlement.", 0);	// First option is always the riskiest TODO:!!!!!
	restOptions.emplace_back("Sleep on the streets.", 0);			// Second is mugging
	restOptions.emplace_back("Sleep in a shared room at a cheap Inn.", REST_SHARED_ROOM_PRICE_CHEAP);
	restOptions.emplace_back("Sleep in a private room at a cheap Inn.", REST_PRIVATE_ROOM_PRICE_CHEAP);
	if (this->maxConnectionSize >= REST_EXPENSIVE_INN_SETTLEMENT_SIZE_TRESHOLD)
	{
		restOptions.emplace_back("Sleep in a private room at an expensive Inn.", REST_PRIVATE_ROOM_PRICE_EXPENSIVE);
	}
}

void Settlement::addRandomShopItem(std::vector<Item>& shopItems, shopType type)
{
	int itemRaritySum;
	std::vector<Item> parsedItems;

	// Generate items this should be in the location constructor
	if (type == SHOP_TYPE_ARMOR) {
		itemRaritySum = ItemParser::getInstance().getArmorsRaritySum();
		parsedItems = ItemParser::getInstance().getParsedArmors();
	}
	else if (type == SHOP_TYPE_WEAPON) {
		itemRaritySum = ItemParser::getInstance().getWeaponsRaritySum();
		parsedItems = ItemParser::getInstance().getParsedWeapons();
	}
	else {
		itemRaritySum = ItemParser::getInstance().getConsumablesRaritySum();
		parsedItems = ItemParser::getInstance().getParsedConsumables();
	}

	// shuffle parseditems vector while we do not get an item that is not already present in the vector
	int itemIndex;
	int randomItemNumCounter;
	do {
		randomItemNumCounter = getRandomBetween(0, itemRaritySum);
		std::shuffle(parsedItems.begin(), parsedItems.end(), randomNumberGenerator);
		for (itemIndex = 0; itemIndex < parsedItems.size() - 1; itemIndex++) {
			randomItemNumCounter -= parsedItems[itemIndex].getRarityValue();
			if (randomItemNumCounter <= 0) {
				break;
			}
		}
	} while ((shopItems.size() != 0) && (std::find_if(shopItems.cbegin(), shopItems.cend(),
		[&](const auto& item) {
			return(item.getName() == parsedItems[itemIndex].getName());
		}) != shopItems.cend()));

	shopItems.push_back(parsedItems[itemIndex]);
}

const std::vector<std::string> Settlement::getMenuOptions() const
{
	std::vector<std::string> options;
	for (const auto& shop : settlementShops) {
		options.emplace_back(shop.getShopName());
	}
	return options;
}

Shop& Settlement::getShop(shopType type)
{
	auto it = std::find_if(settlementShops.begin(), settlementShops.end(),
		[&](const auto& shop) {
			return(shop.getShopName() == type);
		});

	if (it != settlementShops.end())
		return *it;
	else
		throw std::runtime_error("shop not found");
}
