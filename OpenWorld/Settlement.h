#pragma once
#include <string>
#include <vector>

using settlementSize = std::string;

class Settlement
{
public:
	Settlement(const std::string& name, const settlementSize& settlementSize, const std::vector<std::string>& possibleDestionations) :
		name(name), settlementSize(settlementSize), possibleDestionations(possibleDestionations) {};

	// Operators

	// Functions

	// Accessors
	inline std::string getName() const { return name; };
	inline std::vector<std::string> const getPossibleDestionations() const { return possibleDestionations; };

	// Modifiers
private:

	std::string name;
	std::vector<std::string> possibleDestionations;
	settlementSize settlementSize;

};

