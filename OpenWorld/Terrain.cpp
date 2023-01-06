#include "Terrain.h"

Terrain::Terrain(const Terrain& otherTerrain) : Place(otherTerrain.name, otherTerrain.previousTerrainName, otherTerrain.isFixed)
{
	enemiesDay = otherTerrain.enemiesDay;
	enemiesNight = otherTerrain.enemiesNight;
	enemiesDayRaritySum = otherTerrain.enemiesDayRaritySum;
	enemiesNightRaritySum = otherTerrain.enemiesNightRaritySum;
	previousTerrainName = otherTerrain.previousTerrainName;
	travelName = otherTerrain.travelName;
	connectionSize = otherTerrain.connectionSize;
}