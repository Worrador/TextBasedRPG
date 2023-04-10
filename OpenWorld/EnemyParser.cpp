#include "EnemyParser.h"

EnemyParser::EnemyParser()
{
    this->parseEnemies();
}

// Maybe first look for source files then start the game..?

EnemyParser::~EnemyParser()
{
    //RAII? -> create book with constructor and release with destructor, but this objects lifetime is longer than that
}

void EnemyParser::parseEnemies()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };

    auto eHandler = ExcelHandler(L"Resources\\Enemies.xlsx");
    const auto& book = eHandler.getBook();

    // Get the enemies
    libxl::Sheet* sheet = book->getSheet(0);
    if (sheet)
    {
        // Iterate rows, we don't need the first one as it only contains the names of columns
        for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
        {
            // Get name of enemy and convert it to string
            const auto& enemyName = converter.to_bytes((sheet->readStr(row, 0)));

            try{
                parsedEnemies.emplace_back(
                    enemyName,
                    static_cast<int>(sheet->readNum(row, 1)),
                    static_cast<int>(sheet->readNum(row, 2)),
                    static_cast<int>(sheet->readNum(row, 3)),
                    static_cast<int>(sheet->readNum(row, 4)),
                    static_cast<int>(sheet->readNum(row, 5)));
            }
            catch (...) {
                std::cerr << "Error occurred while parsing roles: " << std::endl;
            }
        }
    }
}
