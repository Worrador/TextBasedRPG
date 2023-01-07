#include "Terrain.h"




Terrain::Terrain(const std::string& name, const std::string& travelName, const std::string& previousTerrainName, const std::vector<std::string>& followingTerrainNames, 
	std::vector<std::string>& enemiesDay, std::vector<std::string>& enemiesNight, const int& daySum, const int& nightSum) :
	Place(name, previousTerrainName), enemiesDay(enemiesDay), enemiesNight(enemiesNight), enemiesDayRaritySum(daySum),
	enemiesNightRaritySum(nightSum), travelName(travelName)
{
	if ( (followingTerrainNames[0] == "") || followingTerrainNames.size() > 3){
		maxConnectionSize = 3;
	}
	else {
		maxConnectionSize = (int)followingTerrainNames.size();
	}
}


Terrain::Terrain(const Terrain& otherTerrain) : Place(otherTerrain.name, otherTerrain.previousTerrainName, otherTerrain.followingTerrainNames)
{
	enemiesDay = otherTerrain.enemiesDay;
	enemiesNight = otherTerrain.enemiesNight;
	enemiesDayRaritySum = otherTerrain.enemiesDayRaritySum;
	enemiesNightRaritySum = otherTerrain.enemiesNightRaritySum;
	travelName = otherTerrain.travelName;
	maxConnectionSize = otherTerrain.maxConnectionSize;
}