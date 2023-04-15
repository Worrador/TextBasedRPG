#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "Terrain.h"
#include "EnemyParser.h"
#include "IResourceParser.h"
#include "ExcelHandler.h"

class TerrainParser : public IResourceParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    TerrainParser(const TerrainParser&) = delete;
    TerrainParser(TerrainParser&&) = delete;
    TerrainParser& operator=(const TerrainParser&) = delete;
    TerrainParser& operator=(TerrainParser&&) = delete;

    // Static method to return a reference to the single instance
    static TerrainParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static TerrainParser instance;
        return instance;
    }

    // Method to access the parsedItems vector
    inline const int& getResourceError() { return resourceError; }
    inline std::vector<Terrain>& getParsedTerrains() { return parsedTerrains; }
private:
    // Private constructor to prevent direct instantiation
    TerrainParser();
    ~TerrainParser();

    void parseTerrains();

    std::vector<Terrain> parsedTerrains;
};

