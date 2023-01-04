#pragma once
#include "Place.h"

using settlementSize = std::string;

class Settlement : public Place
{
public:
	Settlement(const std::string& name, const settlementSize& settlementSize) :
		Place(name, ""), settlementSize(settlementSize) {};

	// Operators



	// Functions
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " settlement)"); };

	// Accessors

	// Modifiers
private:
	settlementSize settlementSize;

};

