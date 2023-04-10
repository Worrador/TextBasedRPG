#include "SettlementParser.h"

SettlementParser::SettlementParser()
{
    this->parseSettlements();
}

// Maybe first look for source files then start the game..?

SettlementParser::~SettlementParser()
{
    //RAII?
}

void SettlementParser::parseSettlements()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    auto eHandler = ExcelHandler(L"Resources\\Settlements.xlsx");
    const auto& book = eHandler.getBook();

    // Get the Settlements
    libxl::Sheet* sheet = book->getSheet(0);
    if (sheet)
    {
        // Iterate rows, we don't need the first one as it only contains the names of columns, get all the settlement names
        for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
        {
            try{
                parsedSettlements.emplace_back(converter.to_bytes(sheet->readStr(row, 0)), converter.to_bytes(sheet->readStr(row, 1)), static_cast<int>(sheet->readNum(row, 2)));
            }
            catch (...) {
                std::cerr << "Error occurred while parsing settlements." << std::endl;
            }
        }
    }
}