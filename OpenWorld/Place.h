#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>

class Place
{
public:
	Place(std::string name) : name(name), id(++count) {};

	// Operators
	bool operator==(const Place& other) const {
		return id == other.id;
	}

	// Functions

	// Accessors
	inline const std::string getName() const { return name; };

	static int count;

	// Later make it const
	int id;

protected:

	std::string name;

	//Mabye place* vector
	// how to allocate deallocate?
};

