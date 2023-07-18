#pragma once
#include <string>

// Should be an object, with objective, reward and successcriteria, this object shall be passed to the player if he accepts the quest
//using Quest = std::string;
class Quest
{
public:
	Quest(std::string text) : text(text), name(text.substr(0, text.find('\n'))) {};
	const std::string& getName() const { return name; };
	const std::string& getText() const { return text; };

private:
	std::string text;
	std::string name;
};

