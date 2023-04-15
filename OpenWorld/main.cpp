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
using secs = std::chrono::duration<double>;


int main()
{
    // Start parsing resources
    auto time_thread_start = steady_clock::now();
    std::vector<std::future<int>> resourceErrors;

    resourceErrors.emplace_back(std::async(std::launch::async, []() {return RoleParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return ItemParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return EnemyParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return SettlementParser::getInstance().getResourceError(); }));
    resourceErrors.emplace_back(std::async(std::launch::async, []() {return TerrainParser::getInstance().getResourceError(); }));

    using std::chrono::duration;
    duration<double, std::milli> ms_double = steady_clock::now() - time_thread_start;
    std::cout << "Time took to parse: " << ms_double.count() << std::endl;
    _getch();

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
