#include "ResourceParser.h"
#include <sstream>
#include <cwchar>

ResourceParser::ResourceParser()
{
    libxl::Book* book = xlCreateXMLBook();
    if (book->load(L"Resources\\Items.xlsx"))
    {
        // Get the weapons first
        libxl::Sheet* sheet = book->getSheet(0);
        if (sheet)
        {
            // Iterate rows, we don't need the first one as it only contains the names of columns
            for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
            {
                // Get name of item and convert it to string
                std::string nameString;
                auto name = sheet->readStr(row, 0);
                size_t size2 = wcstombs(nullptr, name, 0);
                if (size2 != static_cast<size_t>(-1)) {
                    nameString.resize(size2);
                    wcstombs(&nameString[0], name, size2 + 1);
                }

                // Get roles of item and convert it to string
                std::string roleNamesString;
                auto roleNames = sheet->readStr(row, 1);
                size_t size = wcstombs(nullptr, roleNames, 0);
                if (size != static_cast<size_t>(-1)) {
                    roleNamesString.resize(size);
                    wcstombs(&roleNamesString[0], roleNames, size + 1);
                }


                // Separate roles by ',' and create roles vector
                std::istringstream iss(roleNamesString);
                std::string token = ", ";
                std::vector<Role> roles;
                auto& roleTable = RoleInfo::getInstance().getRoleNames();
                std::string str;
                while (std::getline(iss, str, ',')) {
                    auto findResult = std::find_if(std::begin(roleTable), std::end(roleTable), [&](const std::pair<Role, std::string>& pair)
                    {
                        return pair.second == str;
                    });

                    roles.push_back(findResult->first);
                }

                // Get itemType, a weapon can only be one or two handed
                itemType parsedType = itemType::twoHanded;
                if (sheet->readStr(row, 2) == L"oneHanded") {
                    parsedType = itemType::oneHanded;
                }

                // Create item and add it to list
                Item item(nameString,
                    roles,
                    parsedType,
                    (int)(sheet->readNum(row, 3)),
                    (int)(sheet->readNum(row, 4)),
                    (int)(sheet->readNum(row, 5)),
                    (int)(sheet->readNum(row, 6)));

                parsedItems.push_back(std::move(item));
            }
        }
    }
    std::cout << book->errorMessage();
    book->release();
}


ResourceParser::~ResourceParser() 
{
    //RAII?
}