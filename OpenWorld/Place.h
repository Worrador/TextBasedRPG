#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>

class Place
{
public:
	Place(const std::string& name, const std::string& previousTerrainName, const bool isSettlement = false) :
		name(name), previousTerrainName(previousTerrainName), id(++count), isSettlement(isSettlement) {};

	// Operators

	// Functions
	virtual std::string getTravelName();

	// Accessors
	inline const std::string& getName() const { return name; };
	inline const std::string& getPreviousTerrainName() const { return previousTerrainName; };
	inline const int& getNumOfEntrances() const { return numOfEntrances; };

	static int count;

	// Later make it const
	int id;
	bool isSettlement;

protected:

	std::string name;
	std::string previousTerrainName = "";
	int numOfEntrances = -1;

	//Mabye place* vector
	// how to allocate deallocate?
};

