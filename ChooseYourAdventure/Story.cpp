#include <iostream>
#include "Story.h"

std::string Storylines[3] = {
	u8"Fel�bredsz, nincs rajtad als� gatya \nMit teszel? 1: Sebz�dsz 10-et, vagy 2:felveszed a ruh�dat?",
	u8"A ruh�dban bogarak voltak, magadon hagyod? 1: Igen, 2: Nem",
	u8"Benn maradsz az �g� h�zban? 1: Igen, 2: Nem",
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
	std::cout << "Nyert�l!\n";
}

void Story::lose()
{
	std::cout << "Meghalt�l!\n";
}
