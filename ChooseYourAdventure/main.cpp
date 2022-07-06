#include <iostream>
#include "Player.h"
#include "Story.h"


int main()
{
    Player myPlayer(15);
    Story myStory;

    myStory.start(myPlayer);

}