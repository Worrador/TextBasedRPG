#include "Menu.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
#define UNIQUE -1
#define ENTER '\r'

int Menu::getInputBetween(int lower, int higher)
{
    int choice;
    std::cin >> choice;

    // Validate the player's input
    while (choice < lower || choice > higher || !std::cin) {
        std::cin.clear(); // reset failbit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input

        std::cout << "Invalid input. Please enter a number between " << lower << " and " << higher << "." << std::endl;
        std::cin >> choice;
    }
    return choice;
}

// Static Lines -> Static Fn -> Dynamic Points -> Dynamic Fn
int Menu::menuGenerator(const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamicMenuPoints, 
    const bool isEscapeable, const std::function <void(std::stringstream&)>& staticMenuFn, 
    const std::function <void(std::stringstream&, const int)>& dynamicMenuFn) {

    // Call the pre-menu callback function, if it is provided
    int numberOfMenuPoints = (int)(dynamicMenuPoints.size() - 1);
    int selectedMenuPoint = std::min(numberOfMenuPoints, 0);

    while (1)
    {
        std::stringstream ss;
        ss << "\033c";
        for (auto line: staticMenuLines)
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
                ss << "> ";
            }
            else {
                ss << "  ";
            }
            ss << dynamicMenuPoints[index] << std::endl;
        }

        if (dynamicMenuFn) {
            dynamicMenuFn(ss, selectedMenuPoint);
        }

        std::cout << ss.str();
        if (selectedMenuPoint < 0) {
            _getch();
            return ESCAPE;
        }
        switch ((_getch())) {
        case KEY_UP:
            selectedMenuPoint = (--selectedMenuPoint < 0) ? numberOfMenuPoints : selectedMenuPoint;
            break;
        case KEY_DOWN:
            selectedMenuPoint = (++selectedMenuPoint > numberOfMenuPoints) ? 0 : selectedMenuPoint;
            break;
        case ENTER:
            return selectedMenuPoint;
        case ESCAPE:
            if (isEscapeable)
                return ESCAPE;
            else break;
        default:
            break;
        }
    }

    return 0;

}

Player Menu::playerCreationMenu()
{
    std::cout << "\033c";
    std::cout << "Welcome player!" << std::endl << std::endl << "This is a command line RPG game which you can play using only your keyboard." <<
        std::endl << "You can select between your options using the keyboard arrows and the Enter key." << std::endl << "If you want to step out of the current menu, use the ESC key." << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Let's create your character!" << std::endl << std::endl;

    std::string name;
    std::cout << "Please enter your name!" << std::endl;
    std::cin >> name;


    bool isMale;

    {
        // List of menu points

        std::vector <std::string> staticMenuLines = {
            "What is your gender?"
        };
        std::vector <std::string> dynamicMenuPoints = {
            "Male",
            "Female"
        };

        auto selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, false);
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
    }

    {
        std::vector <std::string> staticMenuLines = {
            "Now choose a class!"
        };
        // List of menu points
        std::vector <std::string> dynamicMenuPoints = {
          "Warrior",
          "Mage",
          "Rouge",
          "Ranger"
        };

        auto selectedMenuPoint = (Role)menuGenerator(staticMenuLines, dynamicMenuPoints, false);
        return Player(name, isMale, selectedMenuPoint);
    }
    // Do not return with std::move as it prohibits copy elision.
}

int Menu::mainMenu()
{
    std::vector <std::string> staticMenuLines = {
        "MAIN MENU"
    };
    // List of menu points
    std::vector <std::string> dynamicMenuPoints = {
        "Travel",
        "Rest",
        "Shop",
        "Player sheet",
        "Quit",
    };

    auto selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, false);

    return selectedMenuPoint;
}

int Menu::travelMenu(Player& player)
{
    if (player.getStamina() < 1) {
        std::cout << std::endl << "You don't have enough stamina to travel." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return ESCAPE;
    }
    player.setStamina(player.getStamina() - 1);
    std::vector <std::string> staticMenuLines = {
    "TRAVEL",
    "",
    "Where do you wish to travel?"
    };
    // List of menu points
    std::vector <std::string> dynamicMenuPoints = {
      "Nearby town, down the road",
      "To the forest",
      "To the Lake",
      "Your moms ass",
      "What do you care?"
    };

    auto selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true);

    return selectedMenuPoint;
}

void Menu::shopMenu(Player& player)
{
    int selectedMenuPoint;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "SHOP"
        };

        std::vector <std::string> dynamicMenuPoints = {
            "Buy",
            "Sell"
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true);

        switch (selectedMenuPoint) {
        case 0:
            buyMenu(player);
            break;
        case 1:
            sellMenu(player);
            break;
        case ESCAPE:
            return;
        default:
            break;
        }
    }
}

void Menu::buyMenu(Player& player)
{

    int selectedMenuPoint;
    std::vector<Item> shopOptions;
    shopOptions.push_back(Item("Sword", { Role::Warrior, Role::Rouge }, itemType::oneHanded, 0, 3, 0, 0));
    shopOptions.push_back(Item("Bow", { Role::Ranger, Role::Rouge }, itemType::twoHanded, 0, 5, 0, -1));
    shopOptions.push_back(Item("Staff", { Role::Mage }, itemType::oneHanded, 0, 7, 0, 0));
    shopOptions.push_back(Item("Great Sword", { Role::Warrior }, itemType::oneHanded, 0, 5, 0, -2));
    shopOptions.push_back(Item("Light armor", { Role::Warrior, Role::Ranger, Role::Rouge, Role::Acolyte }, itemType::chestPiece, 1, 0, 1, -1));
    shopOptions.push_back(Item("Robes", { Role::Warrior, Role::Ranger, Role::Rouge, Role::Acolyte, Role::Mage }, itemType::chestPiece, 1, 0, 0, 0));


    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "BUY"
        };
        std::vector <std::string> dynamicMenuPoints;

        for (auto& option : shopOptions) {
            dynamicMenuPoints.push_back(option.getName());
        }

        auto getStaticPlayerGold = [player](std::stringstream& ss) ->void {
            // Build string stream object
            ss << std::endl << "Gold: " << player.getGold() << std::endl;
        };

        auto getDynamicItemStats = [shopOptions](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            ss << std::endl << "------------------------------------" << std::endl;
            ss << std::endl << "Costs: " << shopOptions[selectedMenuPoint].getBuyGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<Role> roles = shopOptions[selectedMenuPoint].getRoles();

            for (auto roleIndex = 0; roleIndex < roles.size(); roleIndex++) {
                ss << RoleInfo::getInstance().getRoleNames()[roles[roleIndex]];
                if (roleIndex >= roles.size() - 1) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Max HP: " << shopOptions[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << shopOptions[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << shopOptions[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << shopOptions[selectedMenuPoint].getStaminaMax() << std::endl;
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true, getStaticPlayerGold, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE) {
            return;
        }

        if (player.getGold() >= shopOptions[selectedMenuPoint].getBuyGold()) {
            player.setGold(player.getGold() - shopOptions[selectedMenuPoint].getBuyGold());
            // Moving a const object invoks its copy constructor, since const objects cannot be modified
            // We can move item since local variables are not needed anymore
            player.addItem(std::move(shopOptions[selectedMenuPoint]));

            // Delete the moved item
            shopOptions.erase(shopOptions.begin() + selectedMenuPoint);

        }
        else {
            std::cout << "Not enough money." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}
/*
#include <cel/celfile.h>
#include <cel/celdatabase.h>

int main()
{
    // Open the Excel file
    CELFile file("myfile.xlsx");

    // Create a database from the Excel file
    CELDatabase database(file);

    // Iterate through the sheets in the Excel file
    for (int i = 0; i < database.GetSheetCount(); i++)
    {
        // Get the sheet at the current index
        CELSheet sheet = database.GetSheet(i);

        // Iterate through the rows in the sheet
        for (int j = 0; j < sheet.GetRowCount(); j++)
        {
            // Get the row at the current index
            CELRow row = sheet.GetRow(j);

            // Iterate through the cells in the row
            for (int k = 0; k < row.GetCellCount(); k++)
            {
                // Get the cell at the current index
                CELValue cell = row.GetCell(k);

                // Do something with the cell value
                // ...
            }
        }
    }

    return 0;
}
*/

void Menu::sellMenu(Player& player)
{
}

int Menu::restMenu(Player& player)
{
    int selectedMenuPoint;

    auto getStaticPlayerGold = [player](std::stringstream& ss) ->void {
        // Build string stream object
        ss << std::endl << "Gold: " << player.getGold() << std::endl;
    };

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "REST"
        };

        std::vector <std::string> dynamicMenuPoints = {
            "Sleep in the bushes: \t does not cost any gold, restores half of your missing hp and stamina. Chance to get attacked by animals.",
            "Sleep on the street: \t does not cost any gold, restores half of your missing hp and stamina. Chance to get mugged.",
            "Sleep in a shared room at an Inn: \t costs 4 gold, restores your hp and stamina to full.",
            "Sleep in a private room at an Inn: \t costs 6 gold, restores your hp and stamina to full. Enchances some stats for the next fight."
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true, getStaticPlayerGold);

        switch (selectedMenuPoint) {
        case 0:
        case 1:
            player.setHp((int)(std::floor((player.getHpMax() + player.getHp()) / 2)));
            player.setStamina((int)(std::floor((player.getStaminaMax() + player.getStamina()) / 2)));
            return selectedMenuPoint;
        case 2:
            if (player.getGold() >= 4) {
                player.setGold(player.getGold() - 4);
                player.setHp(player.getHpMax());
                player.setStamina(player.getStaminaMax());
                return selectedMenuPoint;
            }
            else {
                std::cout << "Not enough money." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        case 3:
            if (player.getGold() >= 6) {
                player.setGold(player.getGold() - 6);
                player.setHp(player.getHpMax());
                player.setStamina(player.getStaminaMax());
                return selectedMenuPoint;
            }
            else {
                std::cout << "Not enough money." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        case ESCAPE:
            return selectedMenuPoint;
        default:
            break;
        }
    }
}

void Menu::playerSheetMenu(Player& player)
{
    int selectedMenuPoint;

    auto getStaticPlayerInfo = [player](std::stringstream& ss) ->void {
        // Build string stream object
        ss << std::endl;
        ss << "Name: " << player.getName() << std::endl;
        ss << "Class: " << RoleInfo::getInstance().getRoleNames()[player.getRole()] << std::endl;
        ss << "Level: " << player.getLevel() << std::endl;
        ss << "Exp: " << player.getExp() << "/" << player.getExpNext() << std::endl;
        ss << "HP: " << player.getHp() << "/" << player.getHpMax() << std::endl;
        ss << "Attack:  " << player.getDamageMax() << std::endl;
        ss << "Defence: " << player.getDefence() << std::endl;
        ss << "Stamina: " << player.getStamina() << "/" << player.getStaminaMax() << std::endl << std::endl;

        ss << "------------------------------------" << std::endl << std::endl;

        ss << "INVENTORY" << std::endl << std::endl;
        ss << player.getGold() << " gold" << std::endl;
        for (auto& item: player.getInventory()) {
            ss << item.getName() << std::endl;
        }
        ss << std::endl;
    };

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "PLAYER SHEET"
        };

        std::vector <std::string> dynamicMenuPoints = {
            "Equip items",
            "Unequip items"
        };
        if (player.getExp() >= player.getExpNext()) {
            dynamicMenuPoints.push_back("Level up");
        }

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true, getStaticPlayerInfo);

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
void Menu::equipItems(Player& player)
{
    // List already equipped items

    // List inventory.

    // Player can choose between both, when enter is hit then the items equipment status changes


    int selectedMenuPoint;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "EQUIPPED ITEMS:",
            ""
        };

        auto getStaticEquippedItems = [player](std::stringstream& ss) ->void {
            // Build string stream object
            for (auto& equippedItem : player.getEquipment()) {
                ss << "  " << equippedItem.getName() << std::endl;
            }
            ss << std::endl << "------------------------------------" << std::endl;
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
            dynamicMenuPoints.push_back(item.getName());
        }

        auto getDynamicItemStats = [itemList](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            if (selectedMenuPoint < 0) {
                return;
            }
            ss << std::endl << "------------------------------------" << std::endl;
            ss << std::endl << "ITEM STATISTICS: " << std::endl;
            ss << std::endl << "Sells for: " << itemList[selectedMenuPoint].getSellGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<Role> roles = itemList[selectedMenuPoint].getRoles();

            for (auto roleIndex = 0; roleIndex < roles.size(); roleIndex++) {
                ss << RoleInfo::getInstance().getRoleNames()[roles[roleIndex]];
                if (roleIndex >= roles.size() - 1) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Max HP: " << itemList[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << itemList[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << itemList[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << itemList[selectedMenuPoint].getStaminaMax() << std::endl;
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true, getStaticEquippedItems, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE){
            return;
        }
        player.equipItem(selectedMenuPoint);
        std::cout << std::endl;
    }
}


void Menu::unequipItems(Player& player)
{
    // List already equipped items

    // List inventory.

    // Player can choose between both, when enter is hit then the items equipment status changes


    int selectedMenuPoint;

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

        auto getDynamicItemStats = [itemList, player](std::stringstream& ss, const int selectedMenuPoint) ->void {
            // Build string stream object
            ss << "------------------------------------" << std::endl;
            ss << std::endl << "UNEQUIPPED ITEMS: " << std::endl << std::endl;
            for (auto& inventoryItem : player.getInventory()) {
                ss << "  " << inventoryItem.getName() << std::endl;
            }
            if (player.getEquipment().size() == 0) {
                return;
            }
            ss << std::endl << "------------------------------------" << std::endl;
            ss << std::endl << "ITEM STATISTICS: " << std::endl;
            ss << std::endl << "Sells for: " << itemList[selectedMenuPoint].getSellGold() << " gold. " << std::endl;
            ss << "Equipable by: ";
            std::vector<Role> roles = itemList[selectedMenuPoint].getRoles();

            for (auto roleIndex = 0; roleIndex < roles.size(); roleIndex++) {
                ss << RoleInfo::getInstance().getRoleNames()[roles[roleIndex]];
                if (roleIndex >= roles.size() - 1) {
                    break;
                }
                ss << ", ";
            }
            ss << std::endl;
            ss << "Max HP: " << itemList[selectedMenuPoint].getHpMax() << std::endl;
            ss << "Max damage: " << itemList[selectedMenuPoint].getDamageMax() << std::endl;
            ss << "Defence: " << itemList[selectedMenuPoint].getDefence() << std::endl;
            ss << "Max stamina: " << itemList[selectedMenuPoint].getStaminaMax() << std::endl;
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamicMenuPoints, true, nullptr, getDynamicItemStats);

        if (selectedMenuPoint == ESCAPE) {
            return;
        }
        player.unequipItem(selectedMenuPoint);
        std::cout << std::endl;
    }
}

void Menu::levelUp(Player& player)
{
    player.levelUp();
}
