#include "ItemParser.h"

ItemParser::ItemParser()
{
    this->parseItems();
}

// Maybe first look for source files then start the game..?

ItemParser::~ItemParser()
{
    //RAII?
}

void ItemParser::parseItems()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    libxl::Book* book = xlCreateXMLBook();
    if (!book->load(L"Resources\\Items.xlsx")) {
        book->release();
        resourceError = 1;
        return;
    }

    for (int sheet_index = 0; sheet_index < 2; ++sheet_index)
    {
        libxl::Sheet* sheet = book->getSheet(0);
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
            const auto& name_string = converter.to_bytes(name);

            // Get roles of item and convert it to string
            const auto role_names_string = converter.to_bytes(sheet->readStr(row, 1));

            // Separate roles by ',' and create roles vector
            std::istringstream iss(role_names_string);
            std::vector<roleName> roles;
            std::string str;
            while (std::getline(iss, str, ',')) {
                roles.emplace_back(str);
            }

            // Get type of item and convert it to string
            const auto& item_type_string = converter.to_bytes(sheet->readStr(row, 2));

            // Create item and add it to list
            Item item(
                name_string,
                roles,
                item_type_string,
                static_cast<int>(sheet->readNum(row, 3)),
                static_cast<int>(sheet->readNum(row, 4)),
                static_cast<int>(sheet->readNum(row, 5)),
                static_cast<int>(sheet->readNum(row, 6)));

            if (sheet_index == 0) {
                parsedWeaponsRaritySum += item.getRarity();
                parsedWeapons.push_back(std::move(item));
            }
            else {
                parsedArmorsRaritySum += item.getRarity();
                parsedArmors.push_back(std::move(item));
            }
        }
    }
    book->release();
}
