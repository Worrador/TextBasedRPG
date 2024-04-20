// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include "RoleParser.h"
#include "ItemParser.h"
#include "EnemyParser.h"
#include "SettlementParser.h"
#include "TerrainParser.h"
#include <stdio.h>
#include <future>
#include <iostream>
#include <mutex>
#include <chrono>
#include <vector>

using std::chrono::steady_clock;
using std::chrono::duration;


int main()
{
    // Start parsing resources
    std::vector<std::future<int>> resourceErrors;

    resourceErrors.emplace_back(std::async(std::launch::async, []() {return RoleParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return ItemParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return EnemyParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return SettlementParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return TerrainParser::getInstance().getResourceError(); }));

    for (auto index = 0; index < resourceErrors.size(); ++index) {
        if (resourceErrors[index].get()) {
            std::cout << "Resource error at index: " << index;
            return 0;
        }
    }

    // Get game instance
    Game& game = Game::getInstance();
    // If playing is true, then loop the game
    game.gameLoop();

    std::cout << "\033c";

    std::string line = "";
    std::ifstream inFile;
    std::stringstream ss;

    switch (game.getResult()) {
    case gameResult::Lose:
        try {
            inFile.open("Resources\\lose_art.txt");
        }
        catch (...) {
            std::cout << "YOU LOSE";
        }

    case gameResult::Win:
        try {
            inFile.open("Resources\\win_art.txt");
        }
        catch (...) {
            std::cout << "YOU WIN";
        }

 
    case gameResult::Quit:
    default:
        std::cout << "GAME OVER";
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
