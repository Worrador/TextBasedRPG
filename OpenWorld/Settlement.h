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
			connectionSize = 6;
		}
		else if (settlementSize == "medium") {
			connectionSize = 4;
		}
		else {
			connectionSize = 2;
		}
			
		//else (settlementSize == "small")
			
	};

	// Operators



	// Functions
	inline std::string getTravelName() override { return std::string("To " + name + " (A " + settlementSize + " sized settlement)"); };
	inline int getConnectionSize() override { return connectionSize; };

	void setConnectionSize(const int& connectionSize) override { this->connectionSize = connectionSize; };
	// Accessors

	// Modifiers
private:
	settlementSize settlementSize;
	int connectionSize = 0;

};

