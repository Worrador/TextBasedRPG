// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include "RoleParser.h"
#include "ItemParser.h"
#include "EnemyParser.h"
#include "SettlementParser.h"
#include "TerrainParser.h"
#include <stdio.h>
#include <iostream>

int main()
{
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

    std::cout << "\033c";

    std::string line = "";
    std::ifstream inFile;
    std::stringstream ss;

    if (game.getResult() == gameResult::Lose) {
        try {
            inFile.open("Resources\\lose_art.txt");
        }
        catch (const std::ifstream::failure& e) {
            std::cout << "YOU LOSE";
        }
    }
    else {
        try {
            inFile.open("Resources\\win_art.txt");
        }
        catch (const std::ifstream::failure& e) {
            std::cout << "YOU WIN";
        }

    }
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            ss << line << std::endl;
        }
        inFile.close();
    }

    std::cout << ss.str();
    _getch();
}
