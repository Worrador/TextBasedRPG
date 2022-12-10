#include "Game.h"


Player Game::playerCreation()
{
	std::string name;
	std::cout << "Please input your name!" << std::endl;
	std::cout << "---------" << std::endl;

	std::cin >> name;


	int role;
	std::cout << "Now choose a class!" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "0: Warrior" << std::endl;
	std::cout << "1: Mage" << std::endl;
	std::cout << "2: Rouge" << std::endl;
	std::cout << "3: Ranger" << std::endl;

	std::cin >> role;

	int hpMax, dmg, def, sta;
	switch (role) {
	case 0:
		hpMax = 12;
		dmg = 3;
		def = 2;
		sta = 10;
		break;
	case 1:
		hpMax = 5;
		dmg = 10;
		def = 0;
		sta = 5;
		break;
	case 2:
		hpMax = 8;
		dmg = 7;
		def = 1;
		sta = 7;
		break;
	case 3:
		hpMax = 7;
		dmg = 8;
		def = 1;
		sta = 6;
		break;
	default:
		hpMax = 7;
		dmg = 7;
		def = 1;
		sta = 7;
		break;

	}
	return std::move(Player(name, hpMax, std::floor(dmg/2), dmg, def, sta));
}

Enemy Game::spawnEnemy(int difficulty, int terrain)
{
	return std::move(Enemy("Golem", player.getLevel() * difficulty, 1, difficulty, 1, player.getLevel() * difficulty, player.getLevel() * difficulty));
}




int Game::mainMenu()
{
	std::cout << "\033c";
	std::cout << "MAIN MENU" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "0: Travel" << std::endl;
	std::cout << "1: Shop" << std::endl;
	std::cout << "2: Rest" << std::endl;
	std::cout << "3: Stats" << std::endl;
	std::cout << "4: Inventory" << std::endl;
	std::cout << "5: Quit" << std::endl;

	std::cin >> mainMenuChoice;

	return mainMenuChoice;
}

void Game::printStats()
{
	std::cout << "\033c";
	std::cout << "STATS" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "Name: " << player.getName() << std::endl;
	std::cout << "Level: " << player.getLevel() << std::endl;
	std::cout << "Exp: " << player.getExp() << "/" << player.getExpNext() << std::endl;
	std::cout << "HP: " << player.getHp() << "/" << player.getHpMax() << std::endl;
	std::cout << "Attack:  " << player.getDamageMax() << std::endl;
	std::cout << "Defence: " << player.getDefence() << std::endl;
	std::cout << "Stamina: " << player.getStamina() << "/" << player.getStaminaMax() << std::endl;

	std::cout << std::endl << "0: Return" << std::endl;
	auto Return = 1;
	while (Return != 0) { std::cin >> Return; }
	return;
}

void Game::printInventory()
{
	std::cout << "\033c";
	std::cout << "INVENTORY" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "Gold: " << player.getGold() << std::endl;

	std::cout << std::endl << "0: Return" << std::endl;
	auto Return = 1;
	while (Return != 0) { std::cin >> Return; }
	return;
}

int Game::rollBetween(int lower, int higher)
{
	std::mt19937 rng(std::random_device{}());

	std::uniform_int_distribution<> roll_dist(lower, higher);

	return roll_dist(rng);
}

int Game::getInputBetween(int lower, int higher)
{
	int choice;
	std::cin >> choice;

	// Validate the player's input
	while (choice < lower || choice > higher || !std::cin) {
		std::cin.clear(); // reset failbit
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input

		std::cout << "Invalid input. Please enter a number between 0 and 2." << std::endl;
		std::cin >> choice;
	}
	return choice;
}

void Game::travel() 
{
	// Traveling costs stamina,mabye the more items you have, the more it costs
	player.setStamina(player.getStamina() - 1);

	// Chance for an encounter
	int chance = rollBetween(1, 4);
	if (chance > 0) {

		Enemy enemy = spawnEnemy(rollBetween(1, 10), 0);

		std::cout << "\033c";
		std::cout << "You have met an enemy " << enemy.getName() << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << "0: Attack" << std::endl;
		std::cout << "1: Run" << std::endl;
		std::cout << "2: Wait" << std::endl << std::endl;


		switch (getInputBetween(0, 2)) {
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
	}

	std::cout << "Press a button to return.";
	int Return;
	std::cin >> Return;
	return;
}

void Game::fight(Enemy& enemy, bool playerInitialize)
{
	if (playerInitialize) {
		std::uniform_int_distribution<> player_dmg_dist(player.getDamageMin(), player.getDamageMax());
		int dmgPlayer = std::max(0, rollBetween(player.getDamageMin(), player.getDamageMax()) - enemy.getDefence());

		std::cout << "You deal " << dmgPlayer << "damage." << std::endl;
		enemy.setHp(enemy.getHp() - dmgPlayer);
	}

	while ((player.getHp() > 0) && (enemy.getHp() > 0)) {
		int dmgEnemy = std::max(0, rollBetween(enemy.getDamageMin(), enemy.getDamageMax()) - player.getDefence());
		std::cout << "Your enemy deals " << dmgEnemy << "damage.";
		player.setHp(player.getHp() - dmgEnemy);
		if (player.getHp() <= 0) {
			break;
		}

		std::cout << "\t You have " << player.getHp() << " / " << player.getHpMax() << " hp remaining." << std::endl;
		std::uniform_int_distribution<> player_dmg_dist(player.getDamageMin(), player.getDamageMax());
		int dmgPlayer = std::max(0, rollBetween(player.getDamageMin(), player.getDamageMax()) - enemy.getDefence());

		std::cout << "You deal " << dmgPlayer << "damage." << std::endl;
		enemy.setHp(enemy.getHp() - dmgPlayer);
	}

	if (player.getHp() > 0) {
		std::cout << "You have won the battle, your reward is: " << enemy.getGold() << " gold" << std::endl;
		player.setGold(player.getGold() + enemy.getGold());
		player.setExp(player.getExp() + enemy.getExpDrop());
	}
	else {
		std::cout << "You died." << std::endl;
	}
}

void Game::run(Enemy& enemy)
{
	// Running costs stamina,mabye the more items you have, the more it costs
	player.setStamina(player.getStamina() - 2);
}

void Game::wait(Enemy& enemy)
{
	// The enemy might not attack you and you can continue your journey, 
	// this could depend on your level difference, difficulty, terrain and a lot of other things.
	int chance = rollBetween(1, 4);
	if (chance > 3) {
		std::cout << "The " << enemy.getName() << " does not look to attack you. You can continue your journey if you wish to." << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << "0: Attack anyway" << std::endl;
		std::cout << "1: Walk away" << std::endl;


		switch (getInputBetween(0, 1)) {
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
		fight(enemy, false);
	}
}

// Controls the playthrough stages
void Game::gameLoop()
{
	switch (mainMenu())
	{
	case 0:
		travel();
		break;
	case 1:

		break;
	case 2:
		player.setStamina(player.getStaminaMax());
		break;
	case 3:
		printStats();
		break;
	case 4:
		printInventory();
		break;
	case 5:
		playing = false;
		break;
	default:
		break;
	}
	if (player.getHp() <= 0) {
		playing = false;
	}

}


