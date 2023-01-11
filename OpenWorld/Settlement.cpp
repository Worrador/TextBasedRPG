#include "Settlement.h"
#include "ResourceParser.h"

int Settlement::getRandomBetween(int lower, int higher)
{
	std::uniform_int_distribution<> roll_dist(lower, higher);

	return roll_dist(randomNumberGenerator);
}


Settlement::Settlement(const std::string& name, const settlementSizeType& settlementSize, const int& maxConnectionSize)
	: Place(name, ""), settlementSize(settlementSize), randomNumberGenerator(std::random_device{}())
{
	// Error handling in case something goes wrong, settlement size can only be MAXSETTLEMENTSIZE at max
	this->maxConnectionSize = (maxConnectionSize > MAXSETTLEMENTSIZE) ? MAXSETTLEMENTSIZE : maxConnectionSize;

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

}

void Settlement::addRandomShopItem(std::vector<Item>& shopItems, shopType type)
{
	int randomItemNum;
	std::vector<Item> parsedItems;

	// Generate items this should be in the location constructor
	if (type == SHOP_TYPE_ARMOR) {
		randomItemNum = getRandomBetween(0, ResourceParser::getInstance().getWeaponsRaritySum());
		parsedItems = ResourceParser::getInstance().getParsedArmors();
	}
	else if (type == SHOP_TYPE_WEAPON) {
		randomItemNum = getRandomBetween(0, ResourceParser::getInstance().getConsumablesRaritySum());
		parsedItems = ResourceParser::getInstance().getParsedWeapons();
	}
	else {
		randomItemNum = getRandomBetween(0, ResourceParser::getInstance().getConsumablesRaritySum());
		parsedItems = ResourceParser::getInstance().getParsedConsumables();
	}

	// shuffle parseditems vector while we do not get an item that is not already present in the vector
	int itemIndex;
	do {
		itemIndex = -1;
		std::shuffle(parsedItems.begin(), parsedItems.end(), randomNumberGenerator);
		while (randomItemNum > 0) {
			itemIndex++;
			randomItemNum -= parsedItems[itemIndex].getRarity();
		}
	} while (std::find_if(parsedItems.begin(), parsedItems.end(),
		[&](const auto& item) {
			return(item.getName() == parsedItems[itemIndex].getName());
		}) != parsedItems.end());

	shopItems.push_back(parsedItems[itemIndex]);
}

const std::vector<std::string>& Settlement::getMenuOptions()
{
	static std::vector<std::string> options;
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
