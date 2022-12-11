#include "Game.h"

Enemy Game::spawnEnemy(int difficulty, int terrain)
{
	return Enemy("Golem", player.getLevel() * difficulty, 1, difficulty, 1, difficulty, player.getLevel() * difficulty, player.getLevel() * difficulty);
}


void Game::buy()
{
	while (1) {
		std::cout << "\033c";
		std::cout << "Buy" << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << "0: Health potion: \t costs 3 gold, restores your hp to full." << std::endl;
		std::cout << "1: Stamina potion: \t costs 1 gold, restores your stamina to full." << std::endl;
		std::cout << "2: Sword: \t costs 10 gold, wielding this your attack damage increases by 3." << std::endl;
		std::cout << "3: Armor: \t costs 8 gold, equiping this increases your defence skill by 2." << std::endl;
		std::cout << "4: Return." << std::endl;
		std::cout << std::endl << "Gold: " << player.getGold() << std::endl;

		switch (menu.getInputBetween(0, 4)) {
		case 0:
			if (player.getGold() >= 3) {
				player.setGold(player.getGold() - 3);
				player.setHp(player.getHpMax());
			}
			else {
				std::cout << "Not enough money." << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			break;
		case 1:
			break;
		case 2:
			if (player.getGold() >= 10) {
				player.setGold(player.getGold() - 10);
				player.setDamage(player.getDamageMax() + 3);
			}
			else {
				std::cout << "Not enough money." << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			break;
		case 3:
			if (player.getGold() >= 8) {
				player.setGold(player.getGold() - 8);
				player.setDefence(player.getDefence() + 2);
			}
			else {
				std::cout << "Not enough money." << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}
void Game::shop()
{
	std::cout << "\033c";
	std::cout << "Shop" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "0: Buy" << std::endl;
	std::cout << "1: Sell" << std::endl;

	switch (menu.getInputBetween(0, 1)) {
	case 0:
		buy();
		break;
	case 1:
		break;
	default:
		break;
	}
}

int Game::rollBetween(int lower, int higher)
{
	std::mt19937 rng(std::random_device{}());

	std::uniform_int_distribution<> roll_dist(lower, higher);

	return roll_dist(rng);
}

void Game::travel() 
{
	// Traveling costs stamina,maybe the more items you have, the more it costs
	player.setStamina(player.getStamina() - 1);

	// Chance for an encounter
	auto chance = rollBetween(1, 4);
	if (chance > 0) {

		Enemy enemy = spawnEnemy(rollBetween(1, 10), 0);

		std::vector <std::string> staticLines = {
			"You have met an enemy " + enemy.getName()
		};
		std::vector <std::string> dynamiMenuPoints = {
		  "Attack",
		  "Run",
		  "Wait"
		};


		switch (menu.menuGenerator(staticLines, dynamiMenuPoints, false)) {
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
	_getch();
}

void Game::makeAttack(Character& attacker, Character& defender)
{
	if (attacker.getStamina() > 0) {
		int dmgAttacker = std::max(0, rollBetween(attacker.getDamageMin(), attacker.getDamageMax()) - defender.getDefence());
		std::cout << attacker.getName() << " deals " << dmgAttacker << " damage to " << defender.getName() << "." << std::endl;
		defender.setHp(defender.getHp() - dmgAttacker);

		// Fighting costs stamina, maybe the more items you have, the more it costs
		attacker.setStamina(attacker.getStamina() - 1);
	}
	else {
		std::cout << attacker.getName() << " rests for one round and regains some stamina." << std::endl;
		attacker.setStamina(std::min(3, attacker.getStaminaMax()));
	}

}

void Game::fight(Enemy& enemy, bool playerInitialize)
{
	if (playerInitialize) {
		makeAttack(player, enemy);
	}

	while (enemy.getHp() > 0) {
		makeAttack(enemy, player);
		if (player.getHp() <= 0) {
			std::cout << player.getName() << " has died." << std::endl;
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
	// Running costs stamina, maybe the more items you have, the more it costs
	if (player.getStamina() >= 2) {
		player.setStamina(player.getStamina() - 2);
		std::cout << player.getName() << " has run away from battle." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else {
		std::cout << player.getName() << " is too tired to run, so rests for a while to regain some stamina." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		player.setStamina(std::min(3, player.getStaminaMax()));
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
		std::vector <std::string> dynamiMenuPoints = {
		  "Attack anyway",
		  "Walk away"
		};

		switch (menu.menuGenerator(staticLines, dynamiMenuPoints, false)) {
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
	switch (menu.mainMenu())
	{
	case 0:
		travel();
		break;
	case 1:
		shop();
		break;
	case 2:
		player.setStamina(player.getStaminaMax());
		break;
	case 3:
		menu.playerMenu(player);
		break;
	case 4:
		playing = false;
		break;
	default:
		break;
	}
	if (player.getHp() <= 0) {
		playing = false;
	}

}


