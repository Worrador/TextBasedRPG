#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "Terrain.h"
#include "IResourceParser.h"
#include "ExcelHandler.h"

class EnemyParser : public IResourceParser
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
    inline std::vector<Enemy>& getParsedEnemies() { return parsedEnemies; }

private:
    // LESSON: Private constructor to prevent direct instantiation, but this way static and private members can still acces it
    EnemyParser();
    ~EnemyParser();

    void parseEnemies();
    std::vector<Enemy> parsedEnemies;
};

