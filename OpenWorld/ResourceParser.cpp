#include "ResourceParser.h"
#include <sstream>
#include <cwchar>
#include <codecvt>
#include <locale>

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
                parsedRoles.push_back(
                    Role(roleNameString, 
                    (int)(sheet->readNum(row, 1)),
                    (int)(sheet->readNum(row, 2)),
                    (int)(sheet->readNum(row, 3)),
                    (int)(sheet->readNum(row, 4)),
                    (int)(sheet->readNum(row, 5)),
                    (int)(sheet->readNum(row, 6)),
                    (int)(sheet->readNum(row, 7)),
                    (int)(sheet->readNum(row, 8))));
            }
        }
    }
    book->release();
}

void ResourceParser::parseItems()
{
    libxl::Book* book = xlCreateXMLBook();
    if (!book->load(L"Resources\\Items.xlsx")) {
        book->release();
        return;
    }

    auto to_string = [](const wchar_t* wstr) -> std::string {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(wstr);
    };

    for (int sheet_index = 0; sheet_index < 2; ++sheet_index)
    {
        libxl::Sheet* sheet = book->getSheet(sheet_index);
        if (!sheet) {
            continue;
        }

        // Iterate rows, we don't need the first one as it only contains the names of columns
        for (int row = 1;; ++row)
        {
            // Get name of item and convert it to string
            auto name = sheet->readStr(row, 0);
            if (name == nullptr) {
                break;
            }
            const auto name_string = to_string(name);

            // Get roles of item and convert it to string
            const auto role_names_string = to_string(sheet->readStr(row, 1));

            // Separate roles by ',' and create roles vector
            std::istringstream iss(role_names_string);
            std::string token = ", ";
            std::vector<roleName> roles;
            std::string str;
            while (std::getline(iss, str, ',')) {
                roles.push_back(str);
            }

            // Get type of item and convert it to string
            const auto item_type_string = to_string(sheet->readStr(row, 2));

            // Create item and add it to list
            Item item(name_string,
                roles,
                item_type_string,
                static_cast<int>(sheet->readNum(row, 3)),
                static_cast<int>(sheet->readNum(row, 4)),
                static_cast<int>(sheet->readNum(row, 5)),
                static_cast<int>(sheet->readNum(row, 6)));

            if (sheet_index == 0) {
                parsedWeaponsRaritySum += item.getRarity();
                parsedWeapons.emplace_back(std::move(item));
            }
            else {
                parsedArmorsRaritySum += item.getRarity();
                parsedArmors.emplace_back(std::move(item));
            }
        }
    }
    book->release();
}
