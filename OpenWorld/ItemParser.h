#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "Item.h"
#include "RoleParser.h"
#include "IResourceParser.h"
#include "ExcelHandler.h"

class ItemParser : public IResourceParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    ItemParser(const ItemParser&) = delete;
    ItemParser(ItemParser&&) = delete;
    ItemParser& operator=(const ItemParser&) = delete;
    ItemParser& operator=(ItemParser&&) = delete;

    // Static method to return a reference to the single instance
    static ItemParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static ItemParser instance;
        return instance;
    }

    // Method to access the parsedItems vector
    inline std::vector<Item> getParsedWeapons() { return parsedWeapons; }
    inline std::vector<Item> getParsedArmors() { return parsedArmors; }
    inline std::vector<Item> getParsedConsumables() { return parsedConsumables; }
    inline std::vector<std::string>& getParsedWeaponTypes() { return parsedWeaponTypes; }
    inline std::vector<std::string>& getParsedArmorTypes() { return parsedArmorTypes; }
    inline std::vector<std::string>& getParsedConsumableTypes() { return parsedConsumableTypes; }
    inline int getWeaponsRaritySum() { return parsedWeaponsRaritySum; }
    inline int getArmorsRaritySum() { return parsedArmorsRaritySum; }
    inline int getConsumablesRaritySum() { return parsedConsumablesRaritySum; }

private:
    // Private constructor to prevent direct instantiation
    ItemParser();
    ~ItemParser();

    void parseArmors();
    void parseConsumables();
    void parseWeapons();

    std::vector<Role> parsedRoles;

    std::vector<Item> parsedWeapons;
    int parsedWeaponsRaritySum{};
    std::vector<std::string> parsedWeaponTypes;
    
    std::vector<Item> parsedArmors;
    int parsedArmorsRaritySum{};
    std::vector<std::string> parsedArmorTypes;
    
    std::vector<Item> parsedConsumables;
    int parsedConsumablesRaritySum{};
    std::vector<std::string> parsedConsumableTypes;
};

