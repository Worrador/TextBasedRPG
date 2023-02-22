#include "Game.h"

Enemy Game::spawnEnemy()
{
	// Get list of enemies of current place
	auto currentEnemyNames = worldMap[currentPoint].first->getEnemiesNight();

	// Get enemies that match criteria
	auto parsedEnemies = EnemyParser::getInstance().getParsedEnemies();
	std::vector<Enemy> currentEnemies;


	// If ther are no enemies for some reason, then get enemies from neighboring places
	for (auto ctr = 0; currentEnemyNames.empty(); ctr++) {
		currentEnemyNames = worldMap[worldMap[currentPoint].second[getRandomBetween(0, (int)worldMap[currentPoint].second.size() - 1)]].first->getEnemiesNight();
		if (ctr == 10) {
			std::copy_if(parsedEnemies.cbegin(), parsedEnemies.cend(), std::back_inserter(currentEnemies),
				[&](const auto& enemy) {
					return("Bandit" == enemy.getName());
				});
			return currentEnemies[0];
			break;
		}
	}


	std::copy_if(parsedEnemies.cbegin(), parsedEnemies.cend(), std::back_inserter(currentEnemies),
		[&](const auto& enemy) {
			return(std::find_if(currentEnemyNames.cbegin(), currentEnemyNames.cend(), 
				[&](const auto& enemyName) {
					return(enemyName == enemy.getName());
				}) != currentEnemyNames.cend());
		});

	// Get raritySum of enemies of current place
	auto currentEnemiesRaritySum = 0;

	for (const auto& enemy: currentEnemies) {
		currentEnemiesRaritySum += enemy.getRarity();
	}

	// Generate random number and iterate until an enemy is selected
	int randomEnemyNum = getRandomBetween(0, currentEnemiesRaritySum);
	int enemyIndex = -1;

	while (randomEnemyNum > 0) {
		enemyIndex++;
		randomEnemyNum -= currentEnemies[enemyIndex].getRarity();
	}
	return currentEnemies[enemyIndex];
}

// Get local modifyable variables
static auto settlements = SettlementParser::getInstance().getParsedSettlements();
static auto terrains = TerrainParser::getInstance().getParsedTerrains();
static std::queue<int> placesQueue;
static int worldMapIndex = 0;

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
	bool reqTerrainNotAlreadyAdded = std::find_if(worldMap[currentPlaceIndex].second.cbegin(), worldMap[currentPlaceIndex].second.cend(),
		[&](const auto& p) {
			return worldMap[p].first->getName() == selectedTerrain.getName();
		}) == worldMap[currentPlaceIndex].second.cend();

		return (reqAllowedFollowingTerrain || reqAllowedAnyFollowingTerrain) && (reqCurrentPlaceAllowedAsPrevious || reqAnyPlaceAllowedAsPrevious) && reqNamesAreDifferent && reqTerrainNotAlreadyAdded;
}

void Game::addConnections(int currentPlaceIndex, int maxConnections) {

	if (worldMap.size() >= MAX_WORLD_MAP_SIZE) {
		return;
	}

	// Calculate the number of connections that need to be added
	int connectionsToAdd = getRandomBetween(0, maxConnections - (int)worldMap[currentPlaceIndex].second.size());

	// First add the connections to the map
	for (int i = 0; i < connectionsToAdd; i++) {
		worldMapIndex++;

		// Choose a random settlement or terrain to add to the map
		std::shared_ptr<Place> newPlace;
		if (!getRandomWithChance(SETTLEMENT_TERRAIN_RATIO) || (settlements.empty())) {
			int selectedTerrainIndex = 0;

			// Keep generating a new random number until it fits the requirements
			do {
				selectedTerrainIndex = getRandomBetween(0, (int)terrains.size() - 1);
			} while (!isValidTerrainChoice(selectedTerrainIndex, currentPlaceIndex));

			newPlace = std::make_shared<Terrain>(terrains[selectedTerrainIndex]);
		}
		else {
			int selectedSettlementIndex = getRandomBetween(0, (int)settlements.size() - 1);
			newPlace = std::make_shared<Settlement>(settlements[selectedSettlementIndex]);
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

void Game::generateWorldMap() {

	// Select starting settlement
	auto selected_settlement_index = getRandomBetween(0, (int)settlements.size() - 1);

	// Add to world map
	worldMap.emplace_back(std::make_shared<Settlement>(settlements[selected_settlement_index]), std::vector<int>{});

	// Add to player's map
	player.addToKnownSettlements(currentPoint);

	// Pop from settlements list
	settlements.erase(settlements.begin() + selected_settlement_index);

	// Add connections to settlmenet recursively
	addConnections(0, worldMap[0].first->getMaxConnectionSize());

	// Map not yet populated entirely, retry as long as there are settlements left
	while (!settlements.empty()) {
		int random_ind;
		auto reqNoFollowingAvailable = true, reqSizeLimitReached = true;

		while (reqNoFollowingAvailable || reqSizeLimitReached){
			if (worldMap.size() >= MAX_WORLD_MAP_SIZE) {
				return;
			}
			random_ind = getRandomBetween(0, (int)worldMap.size() - 1);
			for (auto& followingName: worldMap[random_ind].first->getFollowingTerrainNames()) {
				reqNoFollowingAvailable &= (std::find_if(worldMap[random_ind].second.cbegin(), worldMap[random_ind].second.cend(), 
					[&](const auto& mapInd) {
						return worldMap[mapInd].first->getName() == followingName; 
					}) != worldMap[random_ind].second.cend());
			}
			reqSizeLimitReached = ((worldMap[random_ind].first->getMaxConnectionSize() <= worldMap[random_ind].second.size()));
		}
		addConnections(random_ind, worldMap[random_ind].first->getMaxConnectionSize());
	}
}

void Game::playMusic()
{
	std::wstringstream wss;
	wss << L"Resources\\" << player.getRoleName().c_str() << ".wav";


	PlaySound(wss.str().c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	DWORD leftVolume = 2000;
	DWORD rightVolume = 2000;
	waveOutSetVolume(NULL, (leftVolume << 16) | rightVolume);
};

Game::Game() : mainMenuChoice(0), playing(true), player(menu.playerCreationMenu())
{
	playMusic();
	generateWorldMap();
};

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
		return;
	}

	dramaticPause();
	if (getRandomWithChance(CHANCE_ENCOUNTER)) {
		Enemy enemy = spawnEnemy() * player.getLevel();

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

		if (auto settlement = dynamic_cast<Settlement*>(worldMap[currentPoint].first.get()) != nullptr) {
			// Add settlement id if not already present
			const auto& knownSettlements = player.getKnownSettlements();
			if (find(knownSettlements.cbegin(), knownSettlements.cend(), currentPoint) == knownSettlements.cend()) {
				player.addToKnownSettlements(currentPoint);
			}
		}
		else {
			// Add terrain id if not already present
			const auto& knownTerrain = player.getMap(); // Terrains are not stored in themselves
			if (find(knownTerrain.cbegin(), knownTerrain.cend(), currentPoint) == knownTerrain.cend()) {
				player.addToKnownTerrains(currentPoint);
			}
		}

		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_getch();
	}
}

void Game::makeAttack(Character& attacker, Character& defender)
{
	if (attacker.getStamina() > 0) {
		int dmgAttacker = getRandomBetween(attacker.getDamageMin(), attacker.getDamageMax()) - defender.getDefence();
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
		attacker.setStamina(min(FIGHT_REST_STAMINA_INCREMENT, attacker.getStaminaMax()));
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

	std::cout << player.getName() << " has won the battle.";

	// Searching costs stamina, the more items you have, the more it costs
	int staminaNeeded = (int)std::floor(player.getEquipment().size() / 2);

	if (player.getStamina() >= staminaNeeded) {
		player.setStamina(player.getStamina() - (int)std::floor(staminaNeeded / 2));
		std::cout << std::endl << std::endl << "By carefully searching the area " << player.getName() << " stumbles upon the following items: " << std::endl;
		std::cout << "  \x10 " << enemy.getGold() << " gold" << std::endl;
		player.setGold(player.getGold() + enemy.getGold());
		if (getRandomBetween(0, 1)) {
			for (auto& loot : enemy.getLootItems()) {
				std::cout << "  \x10 " << loot.getName() << std::endl;
				player.addItem(loot);
			}
		}
	}
	else {
		std::cout << std::endl << std::endl << player.getName() << " is too tired to search the area, he only finds:" << std::endl;
		std::cout << "  \x10 " << enemy.getGold() << " gold" << std::endl;
		player.setGold(player.getGold() + enemy.getGold());
	}

	
	player.setExp(player.getExp() + enemy.getExpDrop());
	return;
}

void Game::run(Enemy& enemy)
{
	std::cout << "\033c";
	// Running costs stamina, maybe the more items you have, the more it costs or the faster the enemy is
	int staminaNeeded = (int)std::floor((enemy.getStamina() + player.getEquipment().size()) / 2);
	if (player.getStamina() >= staminaNeeded) {
		player.setStamina(player.getStamina() - staminaNeeded);
		std::cout << player.getName() << " has run away from battle." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	else {
		std::cout << player.getName() << " is too tired to run, so rests for a while to regain some stamina." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		player.setStamina(min(player.getRole().getStaminaIncr(), player.getStaminaMax()));
		wait(enemy);
	}
	
}

void Game::wait(Enemy& enemy)
{
	// The enemy might not attack you and you can continue your journey, 
	// this could depend on your level difference, difficulty, terrain and a lot of other things.
	// Lets go with agressivity of attacker
	if (getRandomWithChance((double)enemy.getAggressivity() / (double)MAX_ENEMY_AGGRESSIVITY)) {
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
	dramaticPause();
	switch (restOption)
	{
	case 0: // Chance to get Attacked, if survived then increment health and stamina?
		// Chance for an encounter
		if (getRandomWithChance(CHANCE_ENCOUNTER)) {

			Enemy enemy = spawnEnemy() * player.getLevel();
			std::cout << "You wake up to a noise of a(n) " + enemy.getName() << std::endl;
			_getch();
			fight(enemy, false);
		}
		else {
			std::cout << "You wake somewhat rested." << std::endl;
		}
		break;
	case 1:
		if (getRandomWithChance(CHANCE_REST_MUGGING)) {
			player.setGold((int)std::floor(player.getGold() * (1 - CHANCE_REST_MUGGING)));
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
	while (playing) {
		std::vector <std::string> staticMenuLines = { menu.createBanner(worldMap[currentPoint].first->getName(), worldMap[currentPoint].first->isSettlement()) };
		// List of menu points
		std::vector <std::string> dynamicMenuPoints = {
			MENU_TYPE_TRAVEL,
			MENU_TYPE_REST,
			MENU_TYPE_MAP,
			MENU_TYPE_PLAYER_SHEET,
			MENU_TYPE_QUIT,
		};

		// Add additional menu points before the quit option
		std::vector <std::string> placeMenuOptions = worldMap[currentPoint].first->getMenuOptions();
		dynamicMenuPoints.insert(dynamicMenuPoints.cbegin() + dynamicMenuPoints.size() - 1, 
			placeMenuOptions.cbegin(), placeMenuOptions.cend());

		std::vector<std::string> options = {};

		menu.mainMenuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true);
		if (selectedMenuPoint == ESCAPE) {
				selectedMenuPoint = (int)dynamicMenuPoints.size() - 1;
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_TRAVEL) {
			for (auto index : worldMap[currentPoint].second) {
				if (previousPoint == index) {
					options.emplace_back(worldMap[index].first->getTravelName() + " (go back)");
				}
				else {
					options.emplace_back(worldMap[index].first->getTravelName());
				}

			}
			travel(menu.travelMenu(player, options));
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_MAP) {
			menu.mapMenu(player, currentPoint ,worldMap);
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_REST) {
			rest(menu.restMenu(player, *worldMap[currentPoint].first));
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_PLAYER_SHEET) {
			menu.playerSheetMenu(player);
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_SHOP_ARMOR) {
			auto settlement = dynamic_cast<Settlement*>(worldMap[currentPoint].first.get());
			menu.shopMenu(player, settlement->getShop(MENU_TYPE_SHOP_ARMOR).getShopItems(), ItemParser::getInstance().getParsedArmorTypes());
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_SHOP_WEAPON) {
			auto settlement = dynamic_cast<Settlement*>(worldMap[currentPoint].first.get());
			menu.shopMenu(player, settlement->getShop(MENU_TYPE_SHOP_WEAPON).getShopItems(), ItemParser::getInstance().getParsedWeaponTypes());
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_SHOP_CONSUMABLE) {
			auto settlement = dynamic_cast<Settlement*>(worldMap[currentPoint].first.get());
			menu.shopMenu(player, settlement->getShop(MENU_TYPE_SHOP_CONSUMABLE).getShopItems(), ItemParser::getInstance().getParsedConsumableTypes());
		}
		else if (dynamicMenuPoints[selectedMenuPoint] == MENU_TYPE_QUIT) {
			if (menu.quitMenu() == 0) {
				return;
			}
		}
		else {

		}
	}
}



