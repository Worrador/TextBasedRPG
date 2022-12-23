// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

int main()
{
    // Get res instance
    ResourceParser& res = ResourceParser::getInstance();
    // Get game instance
    Game& game = Game::getInstance();
    // If playing is true, then loop the game
    while (game.getPlaying()) {
        game.gameLoop();
    }
}
