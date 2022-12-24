#include "ResourceParser.h"
#include <sstream>
#include <cwchar>

ResourceParser::ResourceParser()
{
    this->parseRoles();
    this->parseItems();
}


ResourceParser::~ResourceParser() 
{
    //RAII?
}

void ResourceParser::parseRoles()
{
    libxl::Book* book = xlCreateXMLBook();
    if (book->load(L"Resources\\Roles.xlsx"))
    {
        // Get the roles
        libxl::Sheet* sheet = book->getSheet(0);
        if (sheet)
        {
            // Iterate rows, we don't need the first one as it only contains the names of columns
            for (int row = sheet->firstRow() + 1; row < sheet->lastRow(); ++row)
            {
                // Get name of item and convert it to string
                std::string roleNameString;
                auto roleName = sheet->readStr(row, 0);
                size_t size = wcstombs(nullptr, roleName, 0);
                if (size != static_cast<size_t>(-1)) {
                    roleNameString.resize(size);
                    wcstombs(&roleNameString[0], roleName, size + 1);
                }
                parsedRoles.push_back(roleNameString);
            }
        }
    }
    book->release();
}

void ResourceParser::parseItems()
{
    libxl::Book* book = xlCreateXMLBook();
    if (book->load(L"Resources\\Items.xlsx"))
    {
        // Iterate sheets
        for (int sheetIndex = 0; sheetIndex < 2; sheetIndex++) {
            libxl::Sheet* sheet = book->getSheet(sheetIndex);
            if (sheet)
            {
                // Iterate rows, we don't need the first one as it only contains the names of columns
                int row = 1;
                while(1)
                {
                    // Get name of item and convert it to string
                    std::string nameString;
                    auto name = sheet->readStr(row, 0);
                    if (name == nullptr) {
                        break;
                    }
                    size_t size1 = wcstombs(nullptr, name, 0);
                    if (size1 != static_cast<size_t>(-1)) {
                        nameString.resize(size1);
                        wcstombs(&nameString[0], name, size1 + 1);
                    }

                    // Get roles of item and convert it to string
                    std::string roleNamesString;
                    auto roleNames = sheet->readStr(row, 1);
                    size_t size2 = wcstombs(nullptr, roleNames, 0);
                    if (size2 != static_cast<size_t>(-1)) {
                        roleNamesString.resize(size2);
                        wcstombs(&roleNamesString[0], roleNames, size2 + 1);
                    }


                    // Separate roles by ',' and create roles vector
                    std::istringstream iss(roleNamesString);
                    std::string token = ", ";
                    std::vector<Role> roles;
                    auto& roleTable = RoleInfo::getInstance().getRoleNames();
                    std::string str;
                    while (std::getline(iss, str, ',')) {
                        roles.push_back(str);
                    }

                    // Get type of item and convert it to string
                    std::string itemTypeString;
                    auto itemType = sheet->readStr(row, 2);
                    size_t size3 = wcstombs(nullptr, itemType, 0);
                    if (size3 != static_cast<size_t>(-1)) {
                        itemTypeString.resize(size3);
                        wcstombs(&itemTypeString[0], itemType, size3 + 1);
                    }

                    // Create item and add it to list
                    Item item(nameString,
                        roles,
                        itemTypeString,
                        (int)(sheet->readNum(row, 3)),
                        (int)(sheet->readNum(row, 4)),
                        (int)(sheet->readNum(row, 5)),
                        (int)(sheet->readNum(row, 6)));

                    parsedItemRaritySum += item.getRarity();
                    parsedItems.push_back(std::move(item));
                    row++;
                }
            }
        }
    }
    book->release();
}
