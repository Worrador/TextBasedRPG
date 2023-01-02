#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>

class Place
{
public:
	Place(const std::string& name, const std::string& previousTerrainName = "") : 
		name(name), previousTerrainName(previousTerrainName), id(++count) {};

	// Operators
	bool operator==(const Place& other) const {
		return id == other.id;
	}

	// Functions

	// Accessors
	inline const std::string getName() const { return name; };
	inline const std::string& getPreviousTerrainName() const { return previousTerrainName; };


	static int count;

	// Later make it const
	int id;

protected:

	std::string name;
	std::string previousTerrainName = "";

	//Mabye place* vector
	// how to allocate deallocate?
};

