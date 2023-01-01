#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>

class Place
{
public:
	Place(std::string name) : name(name) {};
	// Operators

	// Functions

	// Accessors
	inline const std::string getName() const { return name; };

protected:

	std::string name;
	//Mabye place* vector
	// how to allocate deallocate?
};

