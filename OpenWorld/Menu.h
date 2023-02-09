#pragma once
#include "Player.h"
#include "Place.h"
#include <conio.h>
#include <sstream>
#include <functional> 
#include "RoleParser.h"
#include "Settlement.h"
#include <windows.h>
#include <fstream>

// Constants for menus
constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;
constexpr auto ESCAPE = 27;
constexpr auto UNIQUE = -1;
constexpr auto ENTER = '\r';
constexpr auto ASCII_ART_LENGTH = 44;
constexpr auto MENU_POINT_INDENT = 4;
constexpr auto MENU_INDEXER_SIZE = 2;
constexpr auto MENU_INDEXER_INDENT = MENU_POINT_INDENT + MENU_INDEXER_SIZE;
constexpr auto MENU_DIVIDER_STRING = "\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4";

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

	void mainMenuGenerator(int& selectedMenuPoint, const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamiMenuPoints,
		const bool isEscapeable = true, const std::function <void(std::stringstream&)>& staticMenuFn = nullptr,
		const std::function <void(std::stringstream&, const int)>& dynamicMenuFn = nullptr);

	std::string createBanner(const std::string& title, bool isSettlement = false);

	Player playerCreationMenu();
	int travelMenu(Player& player, std::vector<std::string>& dynamicMenuPoints);
	void shopMenu(Player& player, std::vector<Item>& shopItems, const std::vector<std::string>& sellingOptions);
	void buyMenu(Player& player, std::vector<Item>& shopItems);
	std::vector<Item> sellMenu(Player& player, const std::vector<std::string>& sellingOptions);
	int restMenu(Player& player, Place& currentPlace);
	void playerSheetMenu(Player& player);
	void mapMenu(Player& player, const std::function <std::vector<std::vector<int>>(const std::string_view&)>& pathFinderFn);
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