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

//v3 = rand() % 30 + 1985;

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

void Game::travel() 
{
	int chance = rand() % 1 + 4;
	if (chance > 0) {
		int difficulty = rand() % 1 + 10;
		Enemy enemy("Golem", player.getLevel() * difficulty, 1, difficulty, 1, player.getLevel() * difficulty, player.getLevel() * difficulty);
		fight(enemy);
	}

}

void Game::fight(Enemy& enemy)
{
	std::cout << "\033c";
	std::cout << "You have met an enemy " << enemy.getName() << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "0: Attack" << std::endl;
	std::cout << "1: Run" << std::endl;
	std::cout << "2: Wait" << std::endl << std::endl;

	int choice;
	std::cin >> choice;
	if (choice == 0) {
		while ((player.getHp() > 0) && (enemy.getHp() > 0)) {
			int dmgPlayer = rand() % player.getDamageMin() + player.getDamageMax() - enemy.getDefence();
			std::cout << "You deal " << dmgPlayer << "damage." << std::endl;
			enemy.setHp(enemy.getHp() - dmgPlayer);

			int dmgEnemy = rand() % enemy.getDamageMin() + enemy.getDamageMax() - player.getDefence();
			std::cout << "Your enemy deals " << dmgEnemy << "damage." << std::endl;
			player.setHp(player.getHp() - dmgEnemy);
		}
		if (player.getHp() > 0) {
			std::cout << "You have won the battle, your reward is: " << enemy.getGold() << "gold" << std::endl;
			player.setGold(player.getGold() + enemy.getGold());
			player.setExp(player.getExp() + enemy.getExpDrop());
		}
		else {
			std::cout << "You dieded";
		}

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

}


