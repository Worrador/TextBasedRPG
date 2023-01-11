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
    libxl::Book* book = xlCreateXMLBook();
    if (!book->load(L"Resources\\Settlements.xlsx")) {
        book->release();
        resourceError = 1;
        return;
    }
    // Get the Settlements
    libxl::Sheet* sheet = book->getSheet(0);
    if (sheet)
    {
        // Iterate rows, we don't need the first one as it only contains the names of columns, get all the settlement names
        for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
        {
            parsedSettlements.emplace_back(converter.to_bytes(sheet->readStr(row, 0)), converter.to_bytes(sheet->readStr(row, 1)), static_cast<int>(sheet->readNum(row, 2)));
        }
    }
    book->release();
}