#include "Game.h"


Player Game::playerCreation()
{
	std::string name;
	std::cout << "Plase input your name!" << std::endl;
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
	std::cout << "3: Level up" << std::endl;
	std::cout << "4: Quit" << std::endl;

	std::cin >> mainMenuChoice;

	return mainMenuChoice;
}

// Controls the playthrough stages
void Game::gameLoop()
{
	int choice = mainMenu();
	if (choice == 4)
		playing = false;

}


