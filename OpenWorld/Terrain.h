#pragma once
#include "Place.h"
#include "Enemy.h"

using timeType = std::string;

class Terrain : public Place
{
public:
	Terrain() = default;
	Terrain(const std::string& name, const std::string& travelName, const std::string& previousTerrainName, 
		std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, const int& daySum, const int& nightSum,
		const int& connectionSize, const bool& isFixed) :
		Place(name, previousTerrainName, isFixed), enemiesDay(enemiesDay), enemiesNight(enemiesNight), enemiesDayRaritySum(daySum),
		enemiesNightRaritySum(nightSum), travelName(travelName), connectionSize(connectionSize) {};


	Terrain(const Terrain& otherTerrain);

	// Operators

	// Functions


	// Accessors
	inline const std::vector<std::string>& getEnemiesDay() const { return enemiesDay; };
	inline const std::vector<std::string>& getEnemiesNight() const { return enemiesNight; };
	inline const int& getEnemiesDayRaritySum() const { return enemiesDayRaritySum; }
	inline const int& getEnemiesNightRaritySum() const { return enemiesNightRaritySum; }
	inline std::string getTravelName() override { return travelName; };
	inline int getConnectionSize() override { return connectionSize; };

	// Modifiers
	void setConnectionSize(const int& connectionSize) override { this->connectionSize = connectionSize; };

private:
	std::vector<std::string> enemiesDay;
	std::vector<std::string> enemiesNight;
	std::string travelName;

	int connectionSize;

	int enemiesDayRaritySum = 0;
	int enemiesNightRaritySum = 0;

	//Maybe item vector for questing and stuff later?
	//std::vector<Item>
};