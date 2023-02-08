#pragma once
#include <string>
#include <vector>
#include <memory>

class Place
{
public:
	Place(const std::string& name, const std::string& previousTerrainName = "", const std::vector<std::string>& followingTerrainNames = { "" }) :
		name(name), previousTerrainName(previousTerrainName), followingTerrainNames(followingTerrainNames) {};

	virtual ~Place() {};
	// Operators

	// Functions
	// Make class purely virtual so derived classes must implement this method too
	virtual std::string getTravelName() = 0;
	virtual int getMaxConnectionSize() = 0;
	virtual const std::vector<std::string> getMenuOptions() const  = 0;

	virtual const std::vector<std::string>& getEnemiesDay() const = 0;
	virtual const std::vector<std::string>& getEnemiesNight() const = 0;
	virtual const std::vector<std::pair<std::string, int>>& getRestOptions() const = 0;
	virtual const int& getEnemiesDayRaritySum() const = 0;
	virtual const int& getEnemiesNightRaritySum() const = 0;
	virtual const bool isSettlement() const = 0;
	inline void setToDiscovered() { isDiscovered = true; };

	// Accessors
	inline const std::string& getName() const { return name; };
	inline const std::string& getPreviousTerrainName() const { return previousTerrainName; };
	inline const std::vector<std::string>& getFollowingTerrainNames() const { return followingTerrainNames; };
	inline const bool& getDiscoveredState() const { return isDiscovered; };
	virtual void setMaxConnectionSize(const int& maxConnectionSize) = 0;

	// Later make it const

protected:

	std::string name;
	std::string previousTerrainName;
	std::vector<std::string> followingTerrainNames;
	bool isDiscovered = false;


	//Mabye place* vector
	// how to allocate deallocate?
};

