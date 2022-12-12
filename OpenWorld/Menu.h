#pragma once
#include "Player.h"
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds
#include <conio.h>
#include <sstream>



class Menu
{
public:
	Menu() = default;

	// Operators

	
	// Menu functions:
	int menuGenerator(const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamiMenuPoints, 
		const bool isEscapeable = true, std::stringstream(*staticMenuFn)(const void*) = nullptr, const Player* player = nullptr);


	Player playerCreationMenu();
	int mainMenu();
	void travelMenu(Player& player);
	void shopMenu(Player& player);
	void restMenu(Player& player);
	void playerSheetMenu(Player& player);


	void equipment(Player& player);
	void levelUp(Player& player);
	int getInputBetween(int lower, int higher);

	// Accessors

	// Modifiers

private:

	//std::vector<ItemDrop>
};