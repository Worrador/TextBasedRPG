#pragma once
#include "libxl.h"
#include <sstream>
#include <vector>
#include <codecvt>
#include <functional>
#include "Terrain.h"
#include "Settlement.h"

class ResourceParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    ResourceParser(const ResourceParser&) = delete;
    ResourceParser(ResourceParser&&) = delete;
    ResourceParser& operator=(const ResourceParser&) = delete;
    ResourceParser& operator=(ResourceParser&&) = delete;

    // Static method to return a reference to the single instance
    static ResourceParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static ResourceParser instance;
        return instance;
    }

    // Method to access the parsedItems vector
    inline const int& getResourceError() { return resourceError; }
    inline std::vector<Item>& getParsedWeapons() { return parsedWeapons; }
    inline std::vector<Item>& getParsedArmors() { return parsedArmors; }
    inline std::vector<Item>& getParsedConsumables() { return parsedConsumables; }
    inline std::vector<Role>& getParsedRoles() { return parsedRoles; }
    inline std::vector<Terrain>& getParsedTerrains() { return parsedTerrains; }
    inline std::vector<Settlement>& getParsedSettlements() { return parsedSettlements; }
    inline std::vector<Enemy>& getParsedEnemies() { return parsedEnemies; }
    inline const int& getWeaponsRaritySum() { return parsedWeaponsRaritySum; }
    inline const int& getArmorsRaritySum() { return parsedArmorsRaritySum; }
    inline const int& getConsumablesRaritySum() { return parsedConsumablesRaritySum; }

private:
    // Private constructor to prevent direct instantiation
    ResourceParser();
    ~ResourceParser();

    int resourceError = 0;

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    void parseRoles();
    void parseItems();
    void parseTerrains();
    void parseEnemies();
    void parseSettlements();

    std::vector<Role> parsedRoles;

    std::vector<Item> parsedWeapons;
    int parsedWeaponsRaritySum = 0;
    std::vector<Item> parsedArmors;
    int parsedArmorsRaritySum = 0;
    std::vector<Item> parsedConsumables;
    int parsedConsumablesRaritySum = 0;

    std::vector<Terrain> parsedTerrains;
    std::vector<Settlement> parsedSettlements;

    std::vector<Enemy> parsedEnemies;
};