#pragma once
#include <string>
#include <vector>

class Settlement
{
public:
	Settlement(const std::string& name, const std::vector<std::string>& possibleDestionations) :
		name(name), possibleDestionations(possibleDestionations) {};

	// Operators

	// Functions

	// Accessors
	inline std::string getName() const { return name; };
	inline std::vector<std::string> const getPossibleDestionations() const { return possibleDestionations; };

	// Modifiers
private:

	std::string name;
	std::vector<std::string> possibleDestionations;


};

