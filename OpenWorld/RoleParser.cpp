#include "RoleParser.h"

RoleParser::RoleParser()
{
    this->parseRoles();
}

// Maybe first look for source files then start the game..?

RoleParser::~RoleParser()
{
    //RAII?
}

void RoleParser::parseRoles()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    auto eHandler = ExcelHandler(L"Resources\\Roles.xlsx");
    const auto& book = eHandler.getBook();

    // Get the roles
    libxl::Sheet* sheet = book->getSheet(0);
    if (sheet)
    {
        // Iterate rows, we don't need the first one as it only contains the names of columns
        for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
        {
            // Get name of item and convert it to string

            const auto& roleName = converter.to_bytes((sheet->readStr(row, 0)));

            try {
                parsedRoles.emplace_back(
                    roleName,
                    static_cast<int>(sheet->readNum(row, 1)),
                    static_cast<int>(sheet->readNum(row, 2)),
                    static_cast<int>(sheet->readNum(row, 3)),
                    static_cast<int>(sheet->readNum(row, 4)),
                    static_cast<int>(sheet->readNum(row, 5)),
                    static_cast<int>(sheet->readNum(row, 6)),
                    static_cast<int>(sheet->readNum(row, 7)),
                    static_cast<int>(sheet->readNum(row, 8)));
            }
            catch (...) {
                std::cerr << "Error occurred while parsing roles." << std::endl;
            }

        }
    }

    // Reorder roles based on name
    std::sort(parsedRoles.begin(), parsedRoles.end(), [](const auto& roleA, const auto& roleB) {
            return roleA.getRoleName() < roleB.getRoleName();
        });
}