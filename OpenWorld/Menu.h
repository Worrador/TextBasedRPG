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

	// Functions
	Player playerCreationMenu();
	void playerMenu(Player& player);
	void equipment(Player& player);
	void levelUp(Player& player);
	int getInputBetween(int lower, int higher);

	// Accessors

	// Modifiers

private:

	//std::vector<ItemDrop>
};