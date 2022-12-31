#pragma once
#include "ResourceParser.h"
#include <string>
#include <vector>
#include <memory>
#include <random>

class ResourceParser;

class Place
{
public:
	Place(std::string name) : name(name) {};
	Place(std::string name, Place* previousPlace);
	// Operators

	// Functions

	// Accessors
	inline const std::string getName() const { return name; };
	inline std::vector<std::unique_ptr<Place>> getPossibleDestinations() const { return possibleDestinations; };

	// Modifiers
	void addDestination(Place* destination);

protected:

	std::string name;
	std::vector<std::unique_ptr<Place>> possibleDestinations;
	//Mabye place* vector
	// how to allocate deallocate?
};

