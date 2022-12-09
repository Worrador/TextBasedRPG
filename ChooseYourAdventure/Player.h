#ifndef Player_H
#define Player_H

class Player {

	// Operators

	// Functions

	// Accessors

	// Modifiers
private:
	int hp;

public:
	Player(int hp) :hp(hp){};
	int get_hp();
	void update_hp(int dmg);
};

#endif