#include "ItemParser.h"

ItemParser::ItemParser()
{
    this->parseArmors();
    this->parseConsumables();
    this->parseWeapons();
}

// Maybe first look for source files then start the game..?

ItemParser::~ItemParser()
{
    //RAII?
}

void ItemParser::parseArmors()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    auto eHandler = ExcelHandler(L"Resources\\Enemies.xlsx");
    const auto& book = eHandler.getBook();
    if (!book->load(L"Resources\\Armors.xlsx")) {
        book->release();
        resourceError = 1;
        return;
    }

    libxl::Sheet* sheet = book->getSheet(0);
    if (!sheet) {
        return;
    }

    // Iterate rows, we don't need the first one as it only contains the names of columns
    for (int row{ 1 };; ++row)
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

        // Reorder roles based on name
        std::sort(roles.begin(), roles.end(), [](const auto& roleA, const auto& roleB) {
            return roleA < roleB;
            });

        // Get type of item and convert it to string
        const auto& item_type_string = converter.to_bytes(sheet->readStr(row, 2));

        try{
            // Create item and add it to list
            Item item(
                name_string,
                roles,
                item_type_string,
                static_cast<int>(sheet->readNum(row, 3)),
                static_cast<int>(sheet->readNum(row, 4)),
                static_cast<int>(sheet->readNum(row, 5)),
                static_cast<int>(sheet->readNum(row, 6)));

            parsedArmorsRaritySum += item.getRarityValue();
            if (std::find(parsedArmorTypes.cbegin(), parsedArmorTypes.cend(), item_type_string) == parsedArmorTypes.cend()) {
                parsedArmorTypes.emplace_back(item_type_string);
            }
            parsedArmors.push_back(std::move(item));
        }
        catch (...) {
            std::cerr << "Error occurred while parsing armors." << std::endl;
        }
    }
}

void ItemParser::parseConsumables()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    auto eHandler = ExcelHandler(L"Resources\\Enemies.xlsx");
    const auto& book = eHandler.getBook();
    if (!book->load(L"Resources\\Consumables.xlsx")) {
        book->release();
        resourceError = 1;
        return;
    }

    libxl::Sheet* sheet = book->getSheet(0);
    if (!sheet) {
        return;
    }

    // Iterate rows, we don't need the first one as it only contains the names of columns
    for (int row{ 1 };; ++row)
    {
        // Get name of item and convert it to string
        auto name = sheet->readStr(row, 0);
        if (name == nullptr) {
            break;
        }
        const auto& name_string = converter.to_bytes(name);

        std::vector<roleName> roles;

        const auto& allRoles = RoleParser::getInstance().getParsedRoles();
        for (const auto& role : allRoles) {
            roles.emplace_back(role.getRoleName());
        }
        // Get type of item and convert it to string
        const auto& item_type_string = converter.to_bytes(sheet->readStr(row, 1));

        try{
            // Create item and add it to list
            Item item(
                name_string,
                roles,
                item_type_string,
                static_cast<int>(sheet->readNum(row, 2)),
                static_cast<int>(sheet->readNum(row, 3)),
                static_cast<int>(sheet->readNum(row, 4)),
                static_cast<int>(sheet->readNum(row, 5)));

            parsedConsumablesRaritySum += item.getRarityValue();
            if (std::find(parsedConsumableTypes.cbegin(), parsedConsumableTypes.cend(), item_type_string) == parsedConsumableTypes.cend()) {
                parsedConsumableTypes.emplace_back(item_type_string);
            }
            parsedConsumables.push_back(std::move(item));
        }
        catch (...) {
            std::cerr << "Error occurred while parsing consumables." << std::endl;
        }
    }
}


void ItemParser::parseWeapons()
{
    // Somehow it cannot be handled with unique ptr: 
    // std::unique_ptr <libxl::Book, std::function<void(libxl::Book*)>> book{ xlCreateXMLBook(), [](libxl::Book* book) { book->release(); } };
    auto eHandler = ExcelHandler(L"Resources\\Enemies.xlsx");
    const auto& book = eHandler.getBook();
    if (!book->load(L"Resources\\Weapons.xlsx")) {
        book->release();
        resourceError = 1;
        return;
    }

    libxl::Sheet* sheet = book->getSheet(0);
    if (!sheet) {
        return;
    }

    // Iterate rows, we don't need the first one as it only contains the names of columns
    for (int row{ 1 };; ++row)
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

        // Reorder roles based on name
        std::sort(roles.begin(), roles.end(), [](const auto& roleA, const auto& roleB) {
            return roleA < roleB;
        });

        // Get type of item and convert it to string
        const auto& item_type_string = converter.to_bytes(sheet->readStr(row, 2));

        try{
            // Create item and add it to list
            Item item(
                name_string,
                roles,
                item_type_string,
                static_cast<int>(sheet->readNum(row, 3)),
                static_cast<int>(sheet->readNum(row, 4)),
                static_cast<int>(sheet->readNum(row, 5)),
                static_cast<int>(sheet->readNum(row, 6)));

            parsedWeaponsRaritySum += item.getRarityValue();
            if (std::find(parsedWeaponTypes.cbegin(), parsedWeaponTypes.cend(), item_type_string) == parsedWeaponTypes.cend()) {
                parsedWeaponTypes.emplace_back(item_type_string);
            }
            parsedWeapons.push_back(std::move(item));
        }
        catch (...) {
            std::cerr << "Error occurred while parsing weapons." << std::endl;
        }
    }
}
