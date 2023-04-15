#include "TerrainParser.h"

TerrainParser::TerrainParser()
{
    this->parseTerrains();
}

// Maybe first look for source files then start the game..?

TerrainParser::~TerrainParser()
{
    //RAII?
}

void TerrainParser::parseTerrains()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    auto eHandler = ExcelHandler(L"Resources\\Terrains.xlsx");
    const auto& book = eHandler.getBook();

    // Get the Terrains
    libxl::Sheet* sheet = book->getSheet(0);
    if (sheet)
    {
        // Iterate rows, we don't need the first one as it only contains the names of columns
        for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
        {
            try{
                // Get name of Terrain and convert it to string
                const auto& terrainName = converter.to_bytes((sheet->readStr(row, 0)));

                // Get name of traveling option and convert it to string
                const auto& travelName = converter.to_bytes((sheet->readStr(row, 1)));

                // Get names of required previous terrains
                std::string previousTerrainName = "";
                const auto readPreviousTerrainName = sheet->readStr(row, 2);
                if (readPreviousTerrainName) {
                    previousTerrainName = converter.to_bytes(readPreviousTerrainName);
                }

                // Get names of required following terrains
                const auto followingTerrainName = sheet->readStr(row, 3);
                std::vector<std::string> followingTerrainNames;
                if (followingTerrainName) {
                    previousTerrainName = converter.to_bytes(followingTerrainName);

                    // Separate roles by ';' and create roles vector
                    std::istringstream iss(previousTerrainName);
                    std::vector<std::string> enemiesDay;
                    std::string str;
                    while (std::getline(iss, str, ';')) {
                        followingTerrainNames.emplace_back(str);
                    }
                }
                else {
                    followingTerrainNames.emplace_back("");
                }

                // Get enemies and convert it to string
                const auto enemies_day_string = converter.to_bytes(sheet->readStr(row, 4));

                // Separate roles by ',' and create roles vector
                std::istringstream iss(enemies_day_string);
                std::vector<std::string> enemiesDay;
                std::string str;
                while (std::getline(iss, str, ',')) {
                    enemiesDay.emplace_back(str);
                }

                // Get enemies and convert it to string
                const auto enemies_night_string = converter.to_bytes(sheet->readStr(row, 5));

                // Separate roles by ',' and create roles vector
                std::istringstream iss2(enemies_night_string);
                std::vector<std::string> enemiesNight;
                std::string str2;
                while (std::getline(iss2, str2, ',')) {
                    enemiesNight.emplace_back(str2);
                }

                int enemiesDayRaritySum{};
                int enemiesNightRaritySum{};

                const auto& parsedEnemies = EnemyParser::getInstance().getParsedEnemies();
                for (auto& enemyName : enemiesDay) {
                    auto it = std::find_if(parsedEnemies.cbegin(), parsedEnemies.cend(), [&](const Enemy& current) {return (current.getName() == enemyName); });
                    if (it != parsedEnemies.cend()) {
                        // Enemy found
                        enemiesDayRaritySum += it->getRarity();
                    }
                    else {
                        // Delete enemyName from enemiesDay
                        enemiesDay.erase(std::remove(enemiesDay.begin(), enemiesDay.end(), enemyName), enemiesDay.end());
                    }
                }

                for (auto& enemyName : enemiesNight) {
                    auto it = std::find_if(parsedEnemies.cbegin(), parsedEnemies.cend(), [&](const Enemy& current) {return (current.getName() == enemyName); });
                    if (it != parsedEnemies.cend()) {
                        // Enemy found
                        enemiesNightRaritySum += it->getRarity();
                    }
                    else {
                        // Delete enemyName from enemiesNight
                        enemiesNight.erase(std::remove(enemiesNight.begin(), enemiesNight.end(), enemyName), enemiesNight.end());
                    }
                }

                // Constructing in-place
                parsedTerrains.emplace_back(terrainName, travelName, previousTerrainName, followingTerrainNames, enemiesDay, enemiesNight, enemiesDayRaritySum, enemiesNightRaritySum);
            }
        catch (...) {
            std::cerr << "Error occurred while parsing terrains." << std::endl;
        }
        }
    }
}