#include "Menu.h"

// Static Lines -> Static Fn -> Dynamic Points -> Dynamic Fn
void Menu::menuGenerator(int& selectedMenuPoint, const std::vector<std::string>& staticMenuLines,
    const std::vector<std::string>& dynamicMenuPoints, const bool isEscapeable,
    const std::function <void(std::stringstream&)>& staticMenuFn,
    const std::function <void(std::stringstream&, const int)>& dynamicMenuFn) {

    // Call the pre-menu callback function, if it is provided
    int numberOfMenuPoints = (int)(dynamicMenuPoints.size() - 1);

    while (1)
    {
        std::stringstream ss;
        ss << "\033c";
        for (auto line : staticMenuLines)
        {
            ss << line << std::endl;
        }
        if (staticMenuFn) {
            staticMenuFn(ss);
        }
        ss << std::endl;

        for (auto index = 0; index < dynamicMenuPoints.size(); index++)
        {
            if (index == selectedMenuPoint) {
                ss << "    \xC4\x10 ";
            }
            else {
                ss << "        ";
            }
            ss << dynamicMenuPoints[index] << std::endl;
        }

        if (dynamicMenuFn) {
            dynamicMenuFn(ss, selectedMenuPoint);
        }

        std::cout << ss.str();

        // Error handling in case of empty menu options
        if (selectedMenuPoint < 0) {
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            _getch();
            selectedMenuPoint = ESCAPE;
            return;
        }

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        switch ((_getch())) {
        case KEY_UP:
            selectedMenuPoint = (--selectedMenuPoint < 0) ? numberOfMenuPoints : selectedMenuPoint;
            break;
        case KEY_DOWN:
            selectedMenuPoint = (++selectedMenuPoint > numberOfMenuPoints) ? 0 : selectedMenuPoint;
            break;
        case ENTER:
            return;
        case ESCAPE:
            if (isEscapeable) {
                selectedMenuPoint = ESCAPE;
                return;
            }
            else break;
        default:
            break;
        }
    }

    return;

}

// Static Lines -> Static Fn -> Dynamic Points -> Dynamic Fn
void Menu::mainMenuGenerator(int& selectedMenuPoint, const std::vector<std::string>& staticMenuLines,
    const std::vector<std::string>& dynamicMenuPoints, const bool isEscapeable,
    const std::function <void(std::stringstream&)>& staticMenuFn,
    const std::function <void(std::stringstream&, const int)>& dynamicMenuFn) {

    // Call the pre-menu callback function, if it is provided
    int numberOfMenuPoints = (int)(dynamicMenuPoints.size() - 1);

    while (1)
    {
        std::stringstream ss;
        ss << "\033c";
        for (auto& line : staticMenuLines)
        {
            ss << line << std::endl;
        }
        if (staticMenuFn) {
            staticMenuFn(ss);
        }
        ss << std::string(ASCII_ART_LENGTH, ' ') << '\xB3' << std::endl;

        for (auto index = 0; index < dynamicMenuPoints.size(); index++)
        {
            if (index == selectedMenuPoint) {
                ss << "    \xC4\x10 ";
                ss << dynamicMenuPoints[index];
                ss << std::string(ASCII_ART_LENGTH - (MENU_INDEXER_INDENT + 1) - dynamicMenuPoints[index].length(), ' ') << '\xB3' << std::endl;
            }
            else {
                ss << "        ";
                ss << dynamicMenuPoints[index];
                ss << std::string(ASCII_ART_LENGTH - (MENU_INDEXER_INDENT + 2) - dynamicMenuPoints[index].length(), ' ') << '\xB3' << std::endl;
            }
            
        }
        ss << std::string(ASCII_ART_LENGTH, ' ') << '\xB3' << std::endl;

        if (dynamicMenuFn) {
            dynamicMenuFn(ss, selectedMenuPoint);
        }

        std::cout << ss.str();

        // Error handling in case of empty menu options
        if (selectedMenuPoint < 0) {
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            _getch();
            selectedMenuPoint = ESCAPE;
            return;
        }

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        switch ((_getch())) {
        case KEY_UP:
            selectedMenuPoint = (--selectedMenuPoint < 0) ? numberOfMenuPoints : selectedMenuPoint;
            break;
        case KEY_DOWN:
            selectedMenuPoint = (++selectedMenuPoint > numberOfMenuPoints) ? 0 : selectedMenuPoint;
            break;
        case ENTER:
            return;
        case ESCAPE:
            if (isEscapeable) {
                selectedMenuPoint = ESCAPE;
                return;
            }
            else break;
        default:
            break;
        }
    }

    return;

}



std::string Menu::createBanner(const std::string& title, bool isSettlement)
{
    std::stringstream ss;
    auto banner_width = title.length() + 2;
    const std::string banner = "\xB4 " + title + " \xC3";
    //ss << "\t   \xDA" << std::string(banner_width, '\xC4') << "\xBF" << std::endl;
    //ss << banner << std::endl;
    //ss << "\t   \xC0" << std::string(banner_width, '\xC4') << "\xD9" << std::endl;

    std::string line = "";
    std::ifstream inFile;
    if (isSettlement) {
        inFile.open("Resources\\settlement_art.txt");
    }
    else {
        inFile.open("Resources\\nature_art.txt");
    }
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            ss << line << '\xB3' << std::endl;
        }
    }
    inFile.close();
    int divider_length1 = (int)std::floor((ASCII_ART_LENGTH - banner.length()) / 2);
    int divider_length2 = ASCII_ART_LENGTH - (int)banner.length() - divider_length1;
    

    auto myString = "\xDA" + std::string(banner_width, '\xC4') + "\xBF";
    std::string s = ss.str();
    s.replace(s.end() - (divider_length2 + banner_width + 4), s.end() - (divider_length2 + 2), myString);
    s += std::string(divider_length1, '\xC4') + banner;
    s += std::string(divider_length2, '\xC4') + '\xB4' + '\n';
    s += std::string(divider_length1, ' ') + "\xC0" + std::string(banner_width, '\xC4') + "\xD9" + std::string(divider_length2, ' ') + "\xB3";

    // Named return value optimization is used (NRVO) when only one object can be returned
    return s;
}

Player Menu::playerCreationMenu()
{
    std::cout << "\033c";
    std::cout << "Welcome player!" << std::endl << std::endl << "This is a command line RPG game which you can play using only your keyboard." <<
        std::endl << "You can select between your options using the keyboard arrows and the Enter key." << std::endl << "If you want to step out of the current menu, use the ESC key." << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Let's create your character!" << std::endl << std::endl;

    std::string name;
    std::cout << "Please enter your name!" << std::endl;
    // Clear the buffer to prevent interference from previously entered data
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    std::getline(std::cin, name, '\n');


    bool isMale = true;

    //TODO: maybe get sex later
    /*{
        // List of menu points

        std::vector <std::string> staticMenuLines = {
            "What is your gender?"
        };
        std::vector <std::string> dynamicMenuPoints = {
            "Male",
            "Female"
        };

        int selectedMenuPoint = 0;
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, false);
        switch (selectedMenuPoint) {
        case 0:
            isMale = true;
            break;
        case 1:
            isMale = false;
            break;
        default:
            isMale = true;
            break;
        }
    }*/

    {
        std::vector <std::string> staticMenuLines = {
            "Now choose a class!"
        };
        // List of menu points
        auto& roles = RoleParser::getInstance().getParsedRoles();
        std::vector <std::string> dynamicMenuPoints;

        for (auto& role : roles) {
            dynamicMenuPoints.emplace_back(role.getRoleName());
        }

        // Move so we dont have to copy
        int selectedMenuPoint = 0;
        menuGenerator(selectedMenuPoint, staticMenuLines, std::move(dynamicMenuPoints), false);
        return Player(name, isMale, roles[selectedMenuPoint]);
    }
    // Do not return with std::move as it prohibits copy elision.
}

int Menu::travelMenu(Player& player, std::vector<std::string>& dynamicMenuPoints)
{
    if (player.getStamina() < 1) {
        std::cout << std::endl << "You don't have enough stamina to travel." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return ESCAPE;
    }
    //player.setStamina(player.getStamina() - 1);
    std::vector <std::string> staticMenuLines = {
    "TRAVEL",
    "",
    };

    staticMenuLines.emplace_back("Where do you wish to travel?");

    int selectedMenuPoint = 0;
    menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true);

    return selectedMenuPoint;
}

void Menu::shopMenu(Player& player, std::vector<Item>& shopItems)
{
    int selectedMenuPoint = 0;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "SHOP"
        };

        std::vector <std::string> dynamicMenuPoints = {
            "Buy",
            "Sell"
        };

        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true);

        switch (selectedMenuPoint) {
        case 0:
            buyMenu(player, shopItems);
            break;
        case 1:
            for (auto& item : sellMenu(player)) {
                shopItems.emplace_back(std::move(item));
            }
            break;
        case ESCAPE:
            return;
        default:
            break;
        }
    }
}

void Menu::buyMenu(Player& player, std::vector<Item>& shopItems)
{
    int selectedMenuPoint = 0;
    // Generate items this should be in the location constructor
    
    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "BUY"
        };
        std::vector <std::string> dynamicMenuPoints;

        for (auto& option : shopItems) {
            dynamicMenuPoints.push_back(option.getName());
        }

        auto getStaticPlayerGold = [player](std::stringstream& ss) ->void {
            // Build string stream object
            ss << std::endl << "Gold: " << player.getGold() << std::endl;
        };

        auto getDynamicItemStats = [shopItems](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            if (selectedMenuPoint < 0) {
                return;
            }

            ss << std::endl << MENU_DIVIDER_STRING << std::endl;
            ss << std::endl << "Costs: " << shopItems[selectedMenuPoint].getBuyGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<roleName> roles = shopItems[selectedMenuPoint].getRoles();

            for (auto roleName: roles) {
                ss << roleName;
                if (roleName == roles[roles.size() - 1]) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Item type: " << shopItems[selectedMenuPoint].getItemType() << std::endl;
            ss << "Rarity: " << shopItems[selectedMenuPoint].getRarityName() << std::endl;
            ss << "Max HP: " << shopItems[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << shopItems[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << shopItems[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << shopItems[selectedMenuPoint].getStaminaMax() << std::endl;
        };
        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, getStaticPlayerGold, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE) {
            return;
        }

        if (player.getGold() >= shopItems[selectedMenuPoint].getBuyGold()) {
            player.setGold(player.getGold() - shopItems[selectedMenuPoint].getBuyGold());
            // Moving a const object invoks its copy constructor, since const objects cannot be modified
            // We can move item since local variables are not needed anymore
            player.addItem(std::move(shopItems[selectedMenuPoint]));

            // Delete the moved item
            shopItems.erase(shopItems.begin() + selectedMenuPoint);
            selectedMenuPoint = 0;

        }
        else {
            std::cout << std::endl << "Not enough money." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

// Returns items that the player sold
std::vector<Item> Menu::sellMenu(Player& player)
{
    int selectedMenuPoint = 0;
    // Generate items this should be in the location constructor
    auto& inventroy = player.getInventory();

    std::vector<Item> soldItems;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "SELL"
        };
        std::vector <std::string> dynamicMenuPoints;

        for (auto& option : inventroy) {
            dynamicMenuPoints.push_back(option.getName());
        }

        auto getStaticPlayerGold = [player](std::stringstream& ss) ->void {
            // Build string stream object
            ss << std::endl << "Gold: " << player.getGold() << std::endl;
        };

        auto getDynamicItemStats = [&inventroy](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            if (selectedMenuPoint < 0) {
                return;
            }

            ss << std::endl << MENU_DIVIDER_STRING << std::endl;
            ss << std::endl << "Sells for: " << inventroy[selectedMenuPoint].getSellGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<roleName> roles = inventroy[selectedMenuPoint].getRoles();

            for (auto roleName : roles) {
                ss << roleName;
                if (roleName == roles[roles.size() - 1]) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Item type: " << inventroy[selectedMenuPoint].getItemType() << std::endl;
            ss << "Rarity: " << inventroy[selectedMenuPoint].getRarityName() << std::endl;
            ss << "Max HP: " << inventroy[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << inventroy[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << inventroy[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << inventroy[selectedMenuPoint].getStaminaMax() << std::endl;
        };
        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, getStaticPlayerGold, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE) {
            // Return by value std::move() would prohibit NRVO and if no NRVO can be used std::move will be used anyway.
            return soldItems;
        }

        player.setGold(player.getGold() + inventroy[selectedMenuPoint].getSellGold());
        soldItems.emplace_back(std::move(inventroy[selectedMenuPoint]));
        inventroy.erase(inventroy.begin() + selectedMenuPoint);
    }
}

int Menu::restMenu(Player& player, Place& currentPlace)
{
    int selectedMenuPoint = 0;

    std::vector <std::string> staticMenuLines = {
    "REST"
    };

    std::vector <std::string> dynamicMenuPoints = {};
    std::vector <int> optionPrices = {};

    auto& options = currentPlace.getRestOptions();
    for (auto& option : options) {
        dynamicMenuPoints.emplace_back(option.first);
        optionPrices.emplace_back(option.second);
    }

    if ((int)dynamicMenuPoints.size() == 0) {
        selectedMenuPoint = -1; // indicating error for menugenerator
    }

    auto getStaticPlayerGold = [player](std::stringstream& ss) ->void {
        // Build string stream object
        ss << std::endl << "Gold: " << player.getGold() << std::endl;
    };

    auto getDynamicDescription = [&](std::stringstream& ss, const int& selectedMenuPoint) ->void {
        // Build string stream object
        ss << std::endl << MENU_DIVIDER_STRING << std::endl;
        ss << std::endl << "Costs: " << optionPrices[selectedMenuPoint] << " gold." << std::endl;

        switch (selectedMenuPoint) {
        case 0:
            ss << "Restores half of your missing hp and stamina. Chance to get attacked by animals.";
            break;
        case 1:
            ss << "Restores half of your missing hp and stamina. Chance to get mugged.";
            break;
        case 2:
            ss << "Restores half of your full hp and stamina in addition to your current status.";
            break;
        case 3:
            ss << "Restores your hp and stamina to full.";
            break;
        case 4:
            ss << "Restores your hp and stamina to full. Enchances some stats for the next few fights.";
            break;
        }
    };

    while (1) {
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, getStaticPlayerGold, getDynamicDescription);
        if (selectedMenuPoint == ESCAPE) {
            return selectedMenuPoint;
        }
        // If player has enough gold
        if (player.getGold() >= optionPrices[selectedMenuPoint]) {

            // Remove gold
            player.setGold(player.getGold() - optionPrices[selectedMenuPoint]);

            // Do action according to the selected option
            switch (selectedMenuPoint) {
            case 0:
            case 1:
                player.setHp((int)(std::floor((player.getHpMax() + player.getHp()) / 2)));
                player.setStamina((int)(std::floor((player.getStaminaMax() + player.getStamina()) / 2)));
                break;
            case 2:
                player.setHp(max(player.getHp() + (int)(std::floor(player.getHpMax() / 2)), player.getHpMax()));
                player.setStamina(max(player.getStamina() + (int)(std::floor(player.getStaminaMax() / 2)), player.getStaminaMax()));
                break;
            case 3:
                player.setHp(player.getHpMax());
                player.setStamina(player.getStaminaMax());
                break;
            case 4:
                player.setHp(player.getHpMax());
                player.setStamina(player.getStaminaMax());
                break;
            default:
                return -1;
            }
            return selectedMenuPoint;
        }
        else {
            std::cout << std::endl << std::endl << "Not enough money." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void Menu::playerSheetMenu(Player& player)
{
    int selectedMenuPoint = 0;

    while (1) {

        auto getStaticPlayerInfo = [&player](std::stringstream& ss) ->void {
            // Build string stream object
            ss << std::endl;
            ss << "Name: " << player.getName() << std::endl;
            ss << "Class: " << player.getRoleName() << std::endl;
            ss << "Level: " << player.getLevel() << std::endl;
            ss << "Exp: " << player.getExp() << "/" << player.getExpNext() << std::endl;
            ss << "HP: " << player.getHp() << "/" << player.getHpMax() << std::endl;
            ss << "Attack:  " << player.getDamageMax() << std::endl;
            ss << "Defence: " << player.getDefence() << std::endl;
            ss << "Stamina: " << player.getStamina() << "/" << player.getStaminaMax() << std::endl << std::endl;

            ss << MENU_DIVIDER_STRING << std::endl << std::endl;

            ss << "INVENTORY" << std::endl << std::endl;
            ss << player.getGold() << " gold" << std::endl;
            for (auto& item : player.getInventory()) {
                ss << item.getName() << std::endl;
            }
            ss << std::endl;
        };

        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "PLAYER SHEET"
        };

        std::vector <std::string> dynamicMenuPoints = {
            "Equip or use items",
            "Unequip items"
        };
        if (player.getExp() >= player.getExpNext()) {
            dynamicMenuPoints.push_back("Level up");
        }
        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        // For level up
        if ((int)dynamicMenuPoints.size() <= selectedMenuPoint) {
            selectedMenuPoint = 0; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, getStaticPlayerInfo);

        switch (selectedMenuPoint) {
        case 0:
            equipItems(player);
            break;
        case 1:
            unequipItems(player);
            break;
        case 2:
            levelUp(player);
            break;
        case ESCAPE:
            return;
        default:
            break;
        }
    }
}

int Menu::quitMenu()
{
    int selectedMenuPoint = 0;

    // List of menu points
    std::vector <std::string> staticMenuLines = {
        "Are you sure you want to quit?",
        ""
    };

    // List the eqipped items
    std::vector <std::string> dynamicMenuPoints = {
        "Yes",
        "No"
    };
    menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true);
    return selectedMenuPoint;
}

void Menu::equipItems(Player& player)
{
    int selectedMenuPoint = 0;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "EQUIPPED ITEMS:",
            ""
        };

        auto getStaticEquippedItems = [&player](std::stringstream& ss) ->void {
            // Build string stream object
            for (auto& equippedItem : player.getEquipment()) {
                ss << "  " << equippedItem.getName() << std::endl;
            }
            ss << std::endl << MENU_DIVIDER_STRING << std::endl;
            ss << std::endl << "UNEQUIPPED ITEMS: " << std::endl;
            if (player.getInventory().size() == 0) {
                ss << std::endl << "You don't have anything to equip." << std::endl;
                return;
            }
            
        };

        // List the eqipped items
        std::vector <std::string> dynamicMenuPoints = {};
        std::vector <Item> itemList = player.getInventory();
        for (auto& item : itemList) {
            dynamicMenuPoints.emplace_back(item.getName());
        }

        auto getDynamicItemStats = [itemList](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            if (selectedMenuPoint < 0) {
                return;
            }
            ss << std::endl << MENU_DIVIDER_STRING << std::endl;
            ss << std::endl << "ITEM STATISTICS: " << std::endl;
            ss << std::endl << "Sells for: " << itemList[selectedMenuPoint].getSellGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<roleName> roles = itemList[selectedMenuPoint].getRoles();

            for (auto& roleName : roles) {
                ss << roleName;
                if (roleName == roles[roles.size() - 1]) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Item type: " << itemList[selectedMenuPoint].getItemType() << std::endl;
            ss << "Max HP: " << itemList[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << itemList[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << itemList[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << itemList[selectedMenuPoint].getStaminaMax() << std::endl;
        };
        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, getStaticEquippedItems, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE){
            return;
        }
        player.equipItem(selectedMenuPoint);
        selectedMenuPoint = 0;
        std::cout << std::endl;
    }
}


void Menu::unequipItems(Player& player)
{
    int selectedMenuPoint = 0;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "EQUIPPED ITEMS:",
            ""
        };

        // List the eqipped items
        std::vector <std::string> dynamicMenuPoints = {};
        std::vector <Item> itemList = player.getEquipment();
        for (auto& item: itemList) {
            dynamicMenuPoints.push_back(item.getName());
        }
        if (itemList.size() == 0) {
            staticMenuLines.push_back("You don't have anything to unequip.");
        }

        auto getDynamicItemStats = [&itemList, &player](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            ss << MENU_DIVIDER_STRING << std::endl;
            ss << std::endl << "UNEQUIPPED ITEMS: " << std::endl << std::endl;
            for (auto& inventoryItem : player.getInventory()) {
                ss << "  " << inventoryItem.getName() << std::endl;
            }
            if (player.getEquipment().size() == 0) {
                return;
            }
            ss << std::endl << MENU_DIVIDER_STRING << std::endl;
            ss << std::endl << "ITEM STATISTICS: " << std::endl;
            ss << std::endl << "Sells for: " << itemList[selectedMenuPoint].getSellGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<roleName> roles = itemList[selectedMenuPoint].getRoles();

            for (auto roleIndex = 0; roleIndex < roles.size(); roleIndex++) {
                ss << roles[roleIndex];
                if (roleIndex >= roles.size() - 1) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Item type: " << itemList[selectedMenuPoint].getItemType() << std::endl;
            ss << "Max HP: " << itemList[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << itemList[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << itemList[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << itemList[selectedMenuPoint].getStaminaMax() << std::endl;
        };
        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, nullptr, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE) {
            return;
        }
        player.unequipItem(selectedMenuPoint);
        selectedMenuPoint = 0;
        std::cout << std::endl;
    }
}

void Menu::levelUp(Player& player)
{
    player.levelUp();
}
