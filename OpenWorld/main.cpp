// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include "ResourceParser.h"

int main()
{
    // Parse resources
    if (ResourceParser::getInstance().getResourceError()) {
        std::cout << "Resource error";
        return 0;
    }

    // Get game instance
    Game& game = Game::getInstance();
    // If playing is true, then loop the game
    game.gameLoop();
}
