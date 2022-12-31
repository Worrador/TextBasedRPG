#include "Place.h"
#include "ResourceParser.h"


int static randomBetween(int lower, int higher)
{
    std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<> roll_dist(lower, higher);

    return roll_dist(rng);
}

Place::Place(std::string name, Place* previousPlace) : name(name)
{
    // Make unique called?
    possibleDestinations.emplace_back(previousPlace);

    // Get settlements
    auto& remainingSettlements = ResourceParser::getInstance().getParsedSettlements();

    // Get terrains
    auto& terrains = ResourceParser::getInstance().getParsedTerrains();

    // Add randomly destinations
    for (auto i = 0; i < randomBetween(0, 3); i++)
    {
        if (randomBetween(0, 4)) {  // If not zero
            // Get a random terrain
            auto& randomTerrain = terrains[randomBetween(0, terrains.size() - 1)];

            // If terrain requirement is fulfilled then proceed
            if (randomTerrain.getPreviousTerrainName() == previousPlace->getName()) {
                Terrain terrain = Terrain(randomTerrain, this);
                // Move terrain
                possibleDestinations.emplace_back(std::move(terrain));
            }
        }
        else {
            // Get a random settlement
            auto& randomSettlement = remainingSettlements[randomBetween(0, remainingSettlements.size() - 1)];

            // Add a settlement if there are any
            remainingSettlements[0].addDestination(this);

            // Move settlement
            possibleDestinations.emplace_back(std::move(remainingSettlements[0]));

            // Erase settlement
            remainingSettlements.erase(std::remove(remainingSettlements.begin(), remainingSettlements.end(), remainingSettlements[0]), remainingSettlements.end());

        }
    }
}

void Place::addDestination(Place* destination)
{
    possibleDestinations.emplace_back(destination);
}
