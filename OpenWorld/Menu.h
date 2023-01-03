#pragma once
#include "Player.h"
#include <conio.h>
#include <sstream>
#include <functional> 
#include "ResourceParser.h"
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
#define UNIQUE -1
#define ENTER '\r'

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
	void menuGenerator(int& selectedMenuPoint, const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamiMenuPoints,
		const bool isEscapeable = true, const std::function <void(std::stringstream&)>& staticMenuFn = nullptr,
		const std::function <void(std::stringstream&, const int)>& dynamicMenuFn = nullptr);

	Player playerCreationMenu();
	int travelMenu(Player& player, std::vector<Place*>& possibleDestinations);
	void shopMenu(Player& player, std::vector<Item>& shopItems);
	void buyMenu(Player& player, std::vector<Item>& shopItems);
	void sellMenu(Player& player);
	int restMenu(Player& player);
	void playerSheetMenu(Player& player);
	int quitMenu();


	void equipItems(Player& player);
	void unequipItems(Player& player);
	void levelUp(Player& player);

	// Accessors

	// Modifiers

private:
	menuState menuState;
	//std::vector<ItemDrop>
};