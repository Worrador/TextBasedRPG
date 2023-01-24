#pragma once
#include "libxl.h"
#include <sstream>
#include <vector>
#include <codecvt>
#include <functional>
#include "Item.h"

class ItemParser
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
    inline const int& getResourceError() { return resourceError; }
    inline std::vector<Item>& getParsedWeapons() { return parsedWeapons; }
    inline std::vector<Item>& getParsedArmors() { return parsedArmors; }
    inline std::vector<Item>& getParsedConsumables() { return parsedConsumables; }
    inline std::vector<std::string>& getParsedWeaponTypes() { return parsedWeaponTypes; }
    inline std::vector<std::string>& getParsedArmorTypes() { return parsedArmorTypes; }
    inline std::vector<std::string>& getParsedConsumableTypes() { return parsedConsumableTypes; }
    inline const int& getWeaponsRaritySum() { return parsedWeaponsRaritySum; }
    inline const int& getArmorsRaritySum() { return parsedArmorsRaritySum; }
    inline const int& getConsumablesRaritySum() { return parsedConsumablesRaritySum; }

private:
    // Private constructor to prevent direct instantiation
    ItemParser();
    ~ItemParser();

    int resourceError = 0;

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    void parseItems();

    std::vector<Role> parsedRoles;

    std::vector<Item> parsedWeapons;
    int parsedWeaponsRaritySum = 0;
    std::vector<std::string> parsedWeaponTypes;
    
    std::vector<Item> parsedArmors;
    int parsedArmorsRaritySum = 0;
    std::vector<std::string> parsedArmorTypes;
    
    std::vector<Item> parsedConsumables;
    int parsedConsumablesRaritySum = 0;
    std::vector<std::string> parsedConsumableTypes;
};

