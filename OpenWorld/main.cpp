// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include "RoleParser.h"
#include "ItemParser.h"
#include "EnemyParser.h"
#include "SettlementParser.h"
#include "TerrainParser.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <iostream>

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    // Parse resources
    auto resourceErrors = 0;
    resourceErrors += RoleParser::getInstance().getResourceError();
    resourceErrors += ItemParser::getInstance().getResourceError();
    resourceErrors += EnemyParser::getInstance().getResourceError();
    resourceErrors += SettlementParser::getInstance().getResourceError();
    resourceErrors += TerrainParser::getInstance().getResourceError();

    if (resourceErrors) {
        std::cout << "Resource error: " << resourceErrors;
        return 0;
    }

    // Get game instance
    Game& game = Game::getInstance();
    // If playing is true, then loop the game
    game.gameLoop();
}
