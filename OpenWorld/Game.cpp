#include "Game.h"

Enemy Game::spawnEnemy()
{
	// too big defense means negative damage.. :O
	//return Enemy("Golem", player.getLevel() * difficulty, difficulty, 1, 1, difficulty, player.getLevel() * difficulty, player.getLevel() * difficulty);


	// Generate items this should be in the location constructor
	int randomEnemyNum = 10;
	auto& enemies = ResourceParser::getInstance().getParsedEnemies();

	int enemyIndex = -1;
	while (randomEnemyNum > 0) {
		enemyIndex++;
		randomEnemyNum -= enemies[enemyIndex].getRarity();
	}
	return enemies[enemyIndex]; // Maybe sclale here or after return, need to be careful because of references
}

int Game::rollBetween(int lower, int higher)
{

	std::mt19937 randomNumberGenerator(std::random_device{}());
	std::uniform_int_distribution<> roll_dist(lower, higher);

	return roll_dist(randomNumberGenerator);
}


Item Game::getRandomArmor()
{
	// Generate items this should be in the location constructor
	int randomItemNum = rollBetween(0, ResourceParser::getInstance().getArmorsRaritySum());
	std::vector<Item> parsedItems = ResourceParser::getInstance().getParsedArmors();

	int itemIndex = -1;
	while (randomItemNum > 0) {
		itemIndex++;
		randomItemNum -= parsedItems[itemIndex].getRarity();
	}
	return parsedItems[itemIndex];
}

// Get local modifyable variables
static auto settlements = ResourceParser::getInstance().getParsedSettlements();
static auto terrains = ResourceParser::getInstance().getParsedTerrains();
static std::queue<int> placesQueue;
static int worldMapIndex = 0;

void Game::addConnections(int currentPlaceIndex, int maxConnections) {

	// Calculate the number of connections that need to be added
	int connectionsToAdd = maxConnections - (int)worldMap[currentPlaceIndex].second.size();

	// First add the connections to the map
	for (int i = 0; i < connectionsToAdd; i++) {
		if (settlements.empty()) {
			return;
		}

		worldMapIndex++;

		// Choose a random settlement or terrain to add to the map
		std::unique_ptr<Place> newPlace;
		if (rollBetween(0, 10)) {
			int selectedTerrainIndex;

			// Keep generating a new random number until it fits the requirements
			do {
				selectedTerrainIndex = rollBetween(0, (int)terrains.size() - 1);
			} while (!isValidTerrainChoice(selectedTerrainIndex, currentPlaceIndex));

			newPlace = std::make_unique<Terrain>(terrains[selectedTerrainIndex]);
		}
		else {
			int selectedSettlementIndex = rollBetween(0, (int)settlements.size() - 1);
			newPlace = std::make_unique<Settlement>(settlements[selectedSettlementIndex]);
			settlements.erase(settlements.begin() + selectedSettlementIndex);
		}

		// Add the new place to the world map
		worldMap.emplace_back(std::move(newPlace), std::vector<int>{currentPlaceIndex});

		// Add connection to current node
		placesQueue.push(worldMapIndex);
		worldMap[currentPlaceIndex].second.emplace_back(worldMapIndex);
	}

	// While the queue is not empty, process the nodes in it
	while (!placesQueue.empty()) {
		int queuedPlaceIndex = placesQueue.front();
		placesQueue.pop();

		// Recursively create connections for the current node
		addConnections(queuedPlaceIndex, worldMap[queuedPlaceIndex].first->getMaxConnectionSize());
	}
}

// Returns true if the selected terrain is a valid choice for the current place
bool Game::isValidTerrainChoice(int selectedTerrainIndex, int currentPlaceIndex) {
	const auto& currentPlace = *(worldMap[currentPlaceIndex].first);
	const auto& selectedTerrain = terrains[selectedTerrainIndex];

	// Check if the selected terrain is one of the allowed following terrains
	bool reqAllowedFollowingTerrain = std::find(currentPlace.getFollowingTerrainNames().begin(), currentPlace.getFollowingTerrainNames().end(), selectedTerrain.getName()) != currentPlace.getFollowingTerrainNames().end();

	// Check if the current place is allowed to be followed by any terrain
	bool reqAllowedAnyFollowingTerrain = currentPlace.getFollowingTerrainNames()[0] == "";

	// Check if the selected terrain allows the current place as a previous terrain
	bool reqCurrentPlaceAllowedAsPrevious = selectedTerrain.getPreviousTerrainName() == currentPlace.getName();

	// Check if the selected terrain allows any previous terrain
	bool reqAnyPlaceAllowedAsPrevious = selectedTerrain.getPreviousTerrainName() == "";

	// Check if the selected terrain has the same name as the current place
	bool reqNamesAreDifferent = selectedTerrain.getName() != currentPlace.getName();

	// Check if the selected terrain has already been added to this palce
	bool reqTerrainNotAlreadyAdded = std::find_if(worldMap[currentPlaceIndex].second.begin(), worldMap[currentPlaceIndex].second.end(), 
		[&](const auto& p) {
			return worldMap[p].first->getName() == selectedTerrain.getName();
		}) == worldMap[currentPlaceIndex].second.end();

	return (reqAllowedFollowingTerrain || reqAllowedAnyFollowingTerrain) && (reqCurrentPlaceAllowedAsPrevious || reqAnyPlaceAllowedAsPrevious) && reqNamesAreDifferent && reqTerrainNotAlreadyAdded;
}




void Game::generateWorldMap() {

	// Select starting settlement
	auto selected_settlement_index = rollBetween(0, (int)settlements.size() - 1);

	// Add to world map
	worldMap.emplace_back(std::make_unique<Settlement>(settlements[selected_settlement_index]), std::vector<int>{});

	// Pop from settlements list
	settlements.erase(settlements.begin() + selected_settlement_index);

	// Add connections to settlmenet recursively
	addConnections(0, worldMap[0].first->getMaxConnectionSize());

	// Map not yet populated entirely, retry as long as there are settlements left
	while (!settlements.empty()) {
		int random_ind;
		auto reqNoFollowingAvailable = true, reqSizeLimitReached = true;

		while (reqNoFollowingAvailable || reqSizeLimitReached){
			random_ind = rollBetween(0, (int)worldMap.size() - 1);
			for (auto& followingName: worldMap[random_ind].first->getFollowingTerrainNames()) {
				reqNoFollowingAvailable &= (std::find_if(worldMap[random_ind].second.begin(), worldMap[random_ind].second.end(), [&](const auto& mapInd) {return worldMap[mapInd].first->getName() == followingName; }) != worldMap[random_ind].second.end());
			}
			reqSizeLimitReached = ( /*(worldMap[random_ind].first->getFollowingTerrainNames()[0] == "") && */ (worldMap[random_ind].first->getMaxConnectionSize() <= worldMap[random_ind].second.size()));
		}

		worldMap[random_ind].first->setMaxConnectionSize(worldMap[random_ind].first->getMaxConnectionSize() + 1);
		addConnections(random_ind, worldMap[random_ind].first->getMaxConnectionSize());
	}
}


Game::Game() : mainMenuChoice(0), playing(true), player(menu.playerCreationMenu())
{
	// TODO: replace to cpp
	// Start palying music
	PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	DWORD leftVolume = 2000;
	DWORD rightVolume = 2000;
	waveOutSetVolume(NULL, (leftVolume << 16) | rightVolume);
	shopItems.emplace_back(getRandomWeapon());
	shopItems.emplace_back(getRandomWeapon());
	shopItems.emplace_back(getRandomWeapon());
	shopItems.emplace_back(getRandomArmor());
	shopItems.emplace_back(getRandomArmor());
	generateWorldMap();
};

Item Game::getRandomWeapon()
{
	// Generate items this should be in the location constructor
	int randomItemNum = rollBetween(0, ResourceParser::getInstance().getWeaponsRaritySum());
	auto& parsedItems = ResourceParser::getInstance().getParsedWeapons();

	int itemIndex = -1;
	while (randomItemNum > 0) {
		itemIndex++;
		randomItemNum -= parsedItems[itemIndex].getRarity();
	}
	return parsedItems[itemIndex];
}

void dramaticPause()
{
	std::cout << "\033c";
	std::cout << ".";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << ".";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << ".";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "\033c";
}

void Game::travel(int travelOption)
{
	if (travelOption == ESCAPE) {
		// Give back stamina >.<
		player.setStamina(player.getStamina() + 1);
		return;
	}
	int chance = 0;

	// Chance for an encounter
	chance = rollBetween(0, 4);
	dramaticPause();
	if (chance > 2) {
		Enemy enemy = spawnEnemy() *= player.getLevel();

		std::vector <std::string> staticLines = {
			"You have met an enemy " + enemy.getName()
		};
		std::vector <std::string> dynamicMenuPoints = {
			"Attack",
			"Run",
			"Wait"
		};
		int selectedMenuPoint = 0;
		menu.menuGenerator(selectedMenuPoint, staticLines, dynamicMenuPoints, false);

		switch (selectedMenuPoint) {
		case 0:
			fight(enemy, true);
			break;
		case 1:
			run(enemy);
			break;
		case 2:
			wait(enemy);
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << std::endl;
	}

	if (playing) {
		std::cout << "You have arrived to your destination." << std::endl; 
		previousPoint = currentPoint;
		currentPoint = worldMap[currentPoint].second[travelOption];
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_getch();
	}
}

void Game::makeAttack(Character& attacker, Character& defender)
{
	if (attacker.getStamina() > 0) {
		int dmgAttacker = rollBetween(attacker.getDamageMin(), attacker.getDamageMax()) - defender.getDefence();
		if (dmgAttacker < 0) {
			dmgAttacker = 0;
		}
		std::cout << attacker.getName() << " deals " << dmgAttacker << " damage to " << defender.getName() << "." << std::endl;
		defender.setHp(defender.getHp() - dmgAttacker);

		// Fighting costs stamina, maybe the more items you have, the more it costs
		attacker.setStamina(attacker.getStamina() - 1);
	}
	else {
		std::cout << attacker.getName() << " rests for one round and regains some stamina." << std::endl;
		attacker.setStamina(min(3, attacker.getStaminaMax()));
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(750)); //or continue on button press?
	_getch();
}

void Game::fight(Enemy& enemy, bool playerInitialize)
{
	std::cout << "\033c";
	if (playerInitialize) {
		makeAttack(player, enemy);
	}

	while (enemy.getHp() > 0) {
		makeAttack(enemy, player);
		if (player.getHp() <= 0) {
			std::cout << player.getName() << " has died." << std::endl;
			playing = false;
			return;
		}

		makeAttack(player, enemy);
	}

	std::cout << player.getName() << " has won the battle and is rewarded with " << enemy.getGold() << " gold." << std::endl;
	player.setGold(player.getGold() + enemy.getGold());
	player.setExp(player.getExp() + enemy.getExpDrop());
	return;
}

void Game::run(Enemy& enemy)
{
	std::cout << "\033c";
	// Running costs stamina, maybe the more items you have, the more it costs
	if (player.getStamina() >= 2) {
		player.setStamina(player.getStamina() - 2);
		std::cout << player.getName() << " has run away from battle." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	else {
		std::cout << player.getName() << " is too tired to run, so rests for a while to regain some stamina." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		player.setStamina(min(3, player.getStaminaMax()));
		wait(enemy);
	}
	
}

void Game::wait(Enemy& enemy)
{
	// The enemy might not attack you and you can continue your journey, 
	// this could depend on your level difference, difficulty, terrain and a lot of other things.
	int chance = rollBetween(1, 4);
	if (chance > 3) {
		std::vector <std::string> staticLines = {
			"The " + enemy.getName() + " does not look to attack you. You can continue your journey if you wish to."
		};
		std::vector <std::string> dynamicMenuPoints = {
		  "Attack anyway",
		  "Walk away"
		};
		int selectedMenuPoint = 0;
		menu.menuGenerator(selectedMenuPoint, staticLines, dynamicMenuPoints, false);
		switch (selectedMenuPoint) {
		case 0:
			fight(enemy, true);
			break;
		case 1:
			break;
		default:
			break;
		}
	}
	else {
		std::cout << "The " << enemy.getName() << " looks agressive and attacks you." << std::endl;
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_getch();
		fight(enemy, false);
	}
}

void Game::rest(int restOption)
{
	if (restOption == ESCAPE) {
		return;
	}
	int chance = 0;
	dramaticPause();
	switch (restOption)
	{
	case 0: // Chance to get Attacked, if survived then increment health and stamina?
		// Chance for an encounter
		chance = rollBetween(0, 4);
		if (chance > 0) {

			Enemy enemy = spawnEnemy() *= player.getLevel();
			std::cout << "You wake up to a noise of a(n) " + enemy.getName() << std::endl;

			fight(enemy, false);
		}
		else {
			std::cout << "You wake somewhat rested." << std::endl;
		}
		break;
	case 1:
		chance = rollBetween(0, 4);
		if (chance > 0) {
			player.setGold(player.getGold() - chance);
			std::cout << "You wake somewhat rested. But as you touch your pockets you notice that you have been mugged." << std::endl;
		}
		else {
			std::cout << "You wake somewhat rested." << std::endl;
		}
		break;
	default:
		std::cout << "You wake fully rested." << std::endl;
		break;
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	_getch();
}


// Controls the playthrough stages
void Game::gameLoop()
{
	int selectedMenuPoint = 0;
	while (1) {
		std::vector <std::string> staticMenuLines = { menu.createBanner(worldMap[currentPoint].first->getName()) };
		// List of menu points
		std::vector <std::string> dynamicMenuPoints = {
			"Travel",
			"Rest",
			"Shop",
			"Player sheet",
			"Quit",
		};

		std::vector<std::string> options = {};

		menu.menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true);
		switch (selectedMenuPoint)
		{
		case 0:
			for (auto index : worldMap[currentPoint].second) {
				if (previousPoint == index) {
					options.emplace_back(worldMap[index].first->getTravelName() + " (go back)");
				}
				else {
					options.emplace_back(worldMap[index].first->getTravelName());
				}
				
			}
			travel(menu.travelMenu(player, options));
			break;
		case 1:
			rest(menu.restMenu(player));
			break;
		case 2:
			menu.shopMenu(player, shopItems);
			break;
		case 3:
			menu.playerSheetMenu(player);
			break;
		case 4:
			if (menu.quitMenu() == 0) {
				return;
			}
			break;
		case ESCAPE:
			selectedMenuPoint = 4;
			break;
		default:
			break;
		}
		if (playing != true) {
			return;
		}
	}
}



