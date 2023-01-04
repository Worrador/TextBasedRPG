#pragma once
#include "Place.h"
#include "Enemy.h"

using timeType = std::string;

class Terrain : public Place
{
public:
	Terrain() = default;
	Terrain(const std::string& name, const std::string& travelName, const std::string& previousTerrainName, 
		std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, const int& daySum, const int& nightSum) :
		Place(name, previousTerrainName), enemiesDay(enemiesDay), enemiesNight(enemiesNight), enemiesDayRaritySum(daySum),
		enemiesNightRaritySum(nightSum), travelName(travelName) {};


	Terrain(const Terrain& otherTerrain);

	// Operators

	// Functions
	inline int getConnectionSize() override { return 0; };

	// Accessors
	inline const std::vector<std::string>& getEnemiesDay() const { return enemiesDay; };
	inline const std::vector<std::string>& getEnemiesNight() const { return enemiesNight; };
	inline const int& getEnemiesDayRaritySum() const { return enemiesDayRaritySum; }
	inline const int& getEnemiesNightRaritySum() const { return enemiesNightRaritySum; }
	inline std::string getTravelName() override { return travelName; };
	// Modifiers

private:
	std::vector<std::string> enemiesDay;
	std::vector<std::string> enemiesNight;
	std::string travelName;

	int enemiesDayRaritySum = 0;
	int enemiesNightRaritySum = 0;

	//Maybe item vector for questing and stuff later?
	//std::vector<Item>
};