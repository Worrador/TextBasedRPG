#include "Terrain.h"




Terrain::Terrain(const std::string& name, const std::string& travelName, const std::string& previousTerrainName, const std::vector<std::string>& followingTerrainNames, 
	std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, const int& daySum, const int& nightSum) :
	Place(name, previousTerrainName), enemiesDay(enemiesDay), enemiesNight(enemiesNight), enemiesDayRaritySum(daySum),
	enemiesNightRaritySum(nightSum), travelName(travelName)
{

	// Without a map 2 destination max is plenty
	if ( (followingTerrainNames[0] == "") || followingTerrainNames.size() > MAX_CONNECTION_SIZE_TERRAIN){
		maxConnectionSize = MAX_CONNECTION_SIZE_TERRAIN;
	}
	else {
		maxConnectionSize = (int)followingTerrainNames.size();
	}

	// Add rest options based on Settlement sizer
	restOptions.emplace_back("Sleep on the ground.", 0);
}


Terrain::Terrain(const Terrain& otherTerrain) : Place(otherTerrain.name, otherTerrain.previousTerrainName, otherTerrain.followingTerrainNames)
{
	enemiesDay = otherTerrain.enemiesDay;
	enemiesNight = otherTerrain.enemiesNight;
	enemiesDayRaritySum = otherTerrain.enemiesDayRaritySum;
	enemiesNightRaritySum = otherTerrain.enemiesNightRaritySum;
	travelName = otherTerrain.travelName;
	maxConnectionSize = otherTerrain.maxConnectionSize;
	restOptions = otherTerrain.restOptions;
}

const std::vector<std::string> Terrain::getMenuOptions() const
{
	std::vector<std::string> options;
	return options;
}