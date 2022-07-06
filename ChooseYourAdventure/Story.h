#ifndef Story_H
#define Story_H

#include "Player.h"

class Story {
private:
	int StorylineCounter;

public:
	Story() : StorylineCounter(0) {}

	void start(Player Player);
	void win();
	void lose();
};

#endif
