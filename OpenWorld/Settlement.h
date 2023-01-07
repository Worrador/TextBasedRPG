#pragma once
#include "Place.h"

using settlementSize = std::string;

class Settlement : public Place
{
public:
	Settlement(const std::string& name, const settlementSize& settlementSize) :
		Place(name, ""), settlementSize(settlementSize) 
	{
		if (settlementSize == "large") {
			maxConnectionSize = 6;
		}
		else if (settlementSize == "medium") {
			maxConnectionSize = 4;
		}
		else {
			maxConnectionSize = 2;
		}
			
		//else (settlementSize == "small")
			
	};

	// Operators



	// Functions
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " sized settlement)"); };
	inline int getMaxConnectionSize() override { return maxConnectionSize; };

	void setMaxConnectionSize(const int& maxConnectionSize) override { this->maxConnectionSize = maxConnectionSize; };
	// Accessors

	// Modifiers
private:
	settlementSize settlementSize;
	int maxConnectionSize = 0;

};

