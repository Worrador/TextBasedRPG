// OpenWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"

int main()
{
    srand(time(NULL));

    Game game;

    while (game.getPlaying()) {
        game.gameLoop();
    }
}
