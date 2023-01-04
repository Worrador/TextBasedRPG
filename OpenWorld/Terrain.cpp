#include "Terrain.h"

Terrain::Terrain(const Terrain& otherTerrain) : Place(otherTerrain.name, otherTerrain.previousTerrainName)
{
	enemiesDay = otherTerrain.enemiesDay;
	enemiesNight = otherTerrain.enemiesNight;
	enemiesDayRaritySum = otherTerrain.enemiesDayRaritySum;
	enemiesNightRaritySum = otherTerrain.enemiesNightRaritySum;
	previousTerrainName = otherTerrain.previousTerrainName;
	travelName = otherTerrain.travelName;
}
