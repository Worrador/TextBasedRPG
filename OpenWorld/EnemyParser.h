#pragma once
#include "libxl.h"
#include <sstream>
#include <vector>
#include <codecvt>
#include <functional>
#include "Terrain.h"

class EnemyParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    EnemyParser(const EnemyParser&) = delete;
    EnemyParser(EnemyParser&&) = delete;
    EnemyParser& operator=(const EnemyParser&) = delete;
    EnemyParser& operator=(EnemyParser&&) = delete;

    // Static method to return a reference to the single instance
    static EnemyParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static EnemyParser instance;
        return instance;
    }

    // Method to access the parsedItems vector
    inline const int& getResourceError() { return resourceError; }
    inline std::vector<Enemy>& getParsedEnemies() { return parsedEnemies; }

private:
    // Private constructor to prevent direct instantiation
    EnemyParser();
    ~EnemyParser();

    int resourceError = 0;

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    void parseEnemies();
    std::vector<Enemy> parsedEnemies;
};

