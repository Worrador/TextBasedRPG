#pragma once
#include "Place.h"
#include "Enemy.h"

using timeType = std::string;

class Terrain : public Place
{
public:
	Terrain() = default;
	Terrain(const std::string& name, std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, 
		const int& daySum, const int& nightSum, std::string previousTerrainName = "") :
		Place(name, previousTerrainName), enemiesDay(enemiesDay), enemiesNight(enemiesNight), enemiesDayRaritySum(daySum),
		enemiesNightRaritySum(nightSum) {};

	Terrain(const Terrain& otherTerrain);

	// Operators

	// Functions

	// Accessors
	inline const std::vector<std::string> getEnemiesDay() const { return enemiesDay; };
	inline const std::vector<std::string> getEnemiesNight() const { return enemiesNight; };
	inline const int& getEnemiesDayRaritySum() const { return enemiesDayRaritySum; }
	inline const int& getEnemiesNightRaritySum() const { return enemiesNightRaritySum; }
	// Modifiers

private:
	std::vector<std::string> enemiesDay;
	std::vector<std::string> enemiesNight;

	int enemiesDayRaritySum = 0;
	int enemiesNightRaritySum = 0;

	//Maybe item vector for questing and stuff later?
	//std::vector<Item>
};