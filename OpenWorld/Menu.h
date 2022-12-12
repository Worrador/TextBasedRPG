#pragma once
#include "Player.h"
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds
#include <conio.h>
#include <sstream>

enum class menuState {
	Main = 0,
	Travel,
	Shop,
	Buy,
	Sell,
	Rest,
	PlyaerSheet
};

class Menu
{
public:
	Menu() : menuState(menuState::Main) {};

	// Operators

	
	// Menu functions:
	int menuGenerator(const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamiMenuPoints, 
		const bool isEscapeable = true, void (*staticMenuFn)(std::stringstream&, const void*) = nullptr, const Player* player = nullptr);

	Player playerCreationMenu();
	int mainMenu();
	void travelMenu(Player& player);
	void shopMenu(Player& player);
	void buyMenu(Player& player);
	void sellMenu(Player& player);
	int restMenu(Player& player);
	void playerSheetMenu(Player& player);


	void equipment(Player& player);
	void levelUp(Player& player);
	int getInputBetween(int lower, int higher);

	// Accessors

	// Modifiers

private:
	menuState menuState;
	//std::vector<ItemDrop>
};