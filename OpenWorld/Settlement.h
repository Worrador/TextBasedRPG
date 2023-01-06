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
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " sized settlement)"); };
	inline int getConnectionSize() override { 
		if (settlementSize == "large")
			return 4;
		if (settlementSize == "medium")
			return 3;
		if (settlementSize == "small")
			return 2;
		return 0;
	};
	// Accessors

	// Modifiers
private:
	settlementSize settlementSize;

};

