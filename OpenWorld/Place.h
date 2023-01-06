#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>

class Place
{
public:
	Place(const std::string& name, const std::string& previousTerrainName, const bool isFixed = false) :
		name(name), previousTerrainName(previousTerrainName), id(++count), isFixed(isFixed) {};

	// Operators

	// Functions
	// Make class purely virtual so derived classes must implement this method too
	virtual std::string getTravelName() = 0;
	virtual int getConnectionSize() = 0;

	// Accessors
	inline const std::string& getName() const { return name; };
	inline const std::string& getPreviousTerrainName() const { return previousTerrainName; };

	virtual void setConnectionSize(const int& connectionSize) = 0;

	static int count;

	// Later make it const
	int id;
	bool isFixed = false;

protected:

	std::string name;
	std::string previousTerrainName = "";


	//Mabye place* vector
	// how to allocate deallocate?
};

