#pragma once
#include "Player.h"
#include <conio.h>
#include <sstream>
#include <functional> 
#include "ResourceParser.h"

enum class menuState {
	Main = 0,
	Travel,
	Shop,
	Buy,
	Sell,
	Rest,
	PlayerSheet
};

// Player can manipulate everything through this object
class Menu
{
public:

	// Constructors, explicit to avoid implicit conversions
	explicit Menu() : menuState(menuState::Main) {};

	// Operators

	
	// Menu functions
	int menuGenerator(const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamiMenuPoints, 
		const bool isEscapeable = true, const std::function <void(std::stringstream&)>& staticMenuFn = nullptr,
		const std::function <void(std::stringstream&, const int)>& dynamicMenuFn = nullptr);

	Player playerCreationMenu();
	int mainMenu();
	int travelMenu(Player& player);
	void shopMenu(Player& player);
	void buyMenu(Player& player);
	void sellMenu(Player& player);
	int restMenu(Player& player);
	void playerSheetMenu(Player& player);


	void equipItems(Player& player);
	void unequipItems(Player& player);
	void levelUp(Player& player);
	int getInputBetween(int lower, int higher);

	// Accessors

	// Modifiers

private:
	menuState menuState;
	//std::vector<ItemDrop>
};