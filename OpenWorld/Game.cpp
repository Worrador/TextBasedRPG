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
	std::mt19937 rng(std::random_device{}());

	std::uniform_int_distribution<> roll_dist(lower, higher);

	return roll_dist(rng);
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

void Game::generateWorldMap() {
	auto settlements = ResourceParser::getInstance().getParsedSettlements();
	auto& terrains = ResourceParser::getInstance().getParsedTerrains();

	// Add random nodes to the map
	while(!settlements.empty()) {
		// Choose a random settlement or terrain to add to the map
		if (rollBetween(0, 4)) {
			auto selected_terrain_index = rollBetween(0, (int)terrains.size() - 1);
			Terrain terrain = Terrain(terrains[selected_terrain_index]);	// new is for allocating on heap, this allocates on stack, so destructor call is enough
			worldMap.emplace_back(std::move(terrain), std::vector<Place*>{});
		}
		else {
			auto selected_settlement_index = rollBetween(0, (int)settlements.size() - 1);
			worldMap.emplace_back(std::move(settlements[selected_settlement_index]), std::vector<Place*>{});
			settlements.erase(settlements.begin() + selected_settlement_index);
		}
	}

	// Seed the random number generator with the current time
	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<mapPoint*> nodesWithReqs;

	// Connect the nodes on the map
	for (auto& currentPlace : worldMap) {
		// Generate a random number of connections for this node
		int num_connections = 1;

		// Choose the nodes to connect to randomly from the list of all other nodes
		std::vector<Place*> otherNodes;
		otherNodes.reserve(worldMap.size() - 1);  // optional optimization

		// Iterate over the places in the map and extract the pointers to them
		for (auto& otherPlace : worldMap) {
			if (((currentPlace.first.getName() != otherPlace.first.getName()) &&				// skip nodes with the same name
				(currentPlace.first.getPreviousTerrainName() == "") && 
				(otherPlace.first.getPreviousTerrainName() == "")) ||							// and add only if there is no requirement
				(currentPlace.first.getPreviousTerrainName() == otherPlace.first.getName()) ||
				(otherPlace.first.getPreviousTerrainName() == currentPlace.first.getName())) {	// or its satisfied

				otherNodes.emplace_back(&otherPlace.first);
			}
		}

		// Randomize them
		std::shuffle(otherNodes.begin(), otherNodes.end(), gen);

		// Resize
		otherNodes.resize(num_connections);

		// Add the connections to the graph, maybe delete 
		/*
		otherNodes.erase(std::remove_if(std::begin(otherNodes), std::end(otherNodes), 
			[&](auto& current) {
				return  (current->getPreviousTerrainName() != "") && (currentPlace.first.getName() != current->getPreviousTerrainName()); 
			}), std::end(otherNodes));
			*/
		currentPlace.second.insert(currentPlace.second.end(), otherNodes.begin(), otherNodes.end());

		// Add this node to connected node's connections except if already added
		// Iterate connections
		for (auto& currentConnection : currentPlace.second) {

			// Find the place in the map
			for (auto& [otherPlace, otherConnections] : worldMap) {
				if (otherPlace.id == currentConnection->id) {
					// Check if the current node is already in the connections
					auto it = std::find(otherConnections.begin(), otherConnections.end(), &currentPlace.first);
					if (it == otherConnections.end()) {
						// Place was not found in the connections vector
						// Add the connection
						otherConnections.emplace_back(&currentPlace.first);
					}
					break;
				}
			}
		}
	}

	// Delete nodes without connections from nodesWithReqs and connect remaining nodes to random other nodes
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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << ".";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << ".";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "\033c";
}

void Game::travel(int travelOption)
{
	if (travelOption == ESCAPE) {
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

		// Quick and dirty solution
		for (int mapIndex = 0; mapIndex < worldMap.size(); mapIndex++)
		{
			if (worldMap[mapIndex].first.id == worldMap[currentPoint].second[travelOption]->id) {
				currentPoint = mapIndex;
				break;
			}
		}
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
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else {
		std::cout << player.getName() << " is too tired to run, so rests for a while to regain some stamina." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
		std::vector <std::string> staticMenuLines = {
		"MAIN MENU"
		};
		// List of menu points
		std::vector <std::string> dynamicMenuPoints = {
			"Travel",
			"Rest",
			"Shop",
			"Player sheet",
			"Quit",
		};

		menu.menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true);
		switch (selectedMenuPoint)
		{
		case 0:
			travel(menu.travelMenu(player, worldMap[currentPoint].second));
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



