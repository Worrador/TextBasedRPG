#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>

class Place
{
public:
	Place(const std::string& name, const std::string& previousTerrainName = "", const std::vector<std::string>& followingTerrainNames = { "" }) :
		name(name), previousTerrainName(previousTerrainName), followingTerrainNames(followingTerrainNames) {};

	// Operators

	// Functions
	// Make class purely virtual so derived classes must implement this method too
	virtual std::string getTravelName() = 0;
	virtual int getMaxConnectionSize() = 0;
	virtual const std::vector<std::string> getMenuOptions() const  = 0;

	// Accessors
	inline const std::string& getName() const { return name; };
	inline const std::string& getPreviousTerrainName() const { return previousTerrainName; };
	inline const std::vector<std::string>& getFollowingTerrainNames() const { return followingTerrainNames; };

	virtual void setMaxConnectionSize(const int& maxConnectionSize) = 0;

	// Later make it const

protected:

	std::string name;
	std::string previousTerrainName;
	std::vector<std::string> followingTerrainNames;


	//Mabye place* vector
	// how to allocate deallocate?
};

