// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

int main()
{
    // Get game instance
    Game& game = Game::getInstance();
    // If playing is true, then loop the game
    game.gameLoop();
}
