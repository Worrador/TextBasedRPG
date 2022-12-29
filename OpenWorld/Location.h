#pragma once
#include "Enemy.h"
#include <string>
#include <vector>

using timeType = std::string;

class Location
{
public:
	Location() = default;
	Location(const std::string& name, std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, const int& daySum, const int& nightSum) :
		name(name), enemiesDay(enemiesDay), enemiesNight(enemiesNight), enemiesDayRaritySum(daySum), enemiesNightRaritySum(nightSum) {};

	std::string name;
	// Operators

	// Functions

	// Accessors
	inline std::string getName() const { return name; };
	inline std::vector<std::string> const getEnemiesDay() const { return enemiesDay; };
	inline std::vector<std::string> const getEnemiesNight() const { return enemiesNight; };
	inline const int& getEnemiesDayRaritySum() { return enemiesDayRaritySum; }
	inline const int& getEnemiesNightRaritySum() { return enemiesNightRaritySum; }

	// Modifiers

private:
	std::vector<std::string> enemiesDay;
	std::vector<std::string> enemiesNight;

	int enemiesDayRaritySum = 0;
	int enemiesNightRaritySum = 0;

	//Maybe item vector for questing and stuff later?
	//std::vector<Item>
};