#pragma once
#include "Place.h"
#include "Enemy.h"

using timeType = std::string;

class Terrain : public Place
{
public:
	Terrain(const std::string& name, const std::string& travelName, const std::string& previousTerrainName, const std::vector<std::string>& followingTerrainNames,
		std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, const int& daySum, const int& nightSum);


	Terrain(const Terrain& otherTerrain);

	// Operators

	// Functions


	// Accessors
	inline const std::vector<std::string>& getEnemiesDay() const override { return enemiesDay; };
	inline const std::vector<std::string>& getEnemiesNight() const override { return enemiesNight; };
	inline const int& getEnemiesDayRaritySum() const override { return enemiesDayRaritySum; }
	inline const int& getEnemiesNightRaritySum() const override { return enemiesNightRaritySum; }
	inline std::string getTravelName() override { return travelName; };
	inline int getMaxConnectionSize() override { return maxConnectionSize; };
	const std::vector<std::string> getMenuOptions() const override;

	// Modifiers
	void setMaxConnectionSize(const int& maxConnectionSize) override { this->maxConnectionSize = maxConnectionSize; };

private:
	std::vector<std::string> enemiesDay;
	std::vector<std::string> enemiesNight;

	int maxConnectionSize;

	int enemiesDayRaritySum = 0;
	int enemiesNightRaritySum = 0;

	std::string travelName;

	//Maybe item vector for questing and stuff later?
	//std::vector<Item>
};