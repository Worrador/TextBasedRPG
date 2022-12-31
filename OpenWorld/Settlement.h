#pragma once
#include "Place.h"

using settlementSize = std::string;

class Settlement : public Place
{
public:
	Settlement(const std::string& name, const settlementSize& settlementSize) :
		Place(name), settlementSize(settlementSize) {};

	// Operators
	bool operator==(const Settlement& settlement1, const Settlement& settlement2);

	// Functions

	// Accessors

	// Modifiers
private:
	settlementSize settlementSize;

};

