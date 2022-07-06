#include <iostream>
#include "Story.h"

const char* Storylines[3] = {
	"Felébredsz, nincs rajtad alsó gatya \nMit teszel? 1: Sebzõdsz 10-et, vagy 2:felveszed a ruhádat?",
	"A ruhádban bogarak voltak, magadon hagyod? 1: Igen, 2: Nem",
	"Benn maradsz az égõ házban? 1: Igen, 2: Nem",
};

void Story::start(Player Player)
{
	this->StorylineCounter = 0;
	while (Player.get_hp() > 0) 
	{
		std::cout << Storylines[this->StorylineCounter];
		int answer;
		std::cin >> answer;
		if (answer == 1)
		{
			Player.update_hp(10);
			this->StorylineCounter++;
		}
		else if(answer == 2)
			this->StorylineCounter++;

		if (this->StorylineCounter >= 3)
		{
			win();
			break;
		}
	}

	if (this->StorylineCounter < 3)
	{
		lose();
	}
}

void Story::win()
{
	std::cout << "Nyertél!\n";
}

void Story::lose()
{
	std::cout << "Meghaltál!\n";
}
