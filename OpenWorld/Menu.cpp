#include "Menu.h"

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
void Menu::menuGenerator(int& selectedMenuPoint, const std::vector<std::string>& staticMenuLines, 
    const std::vector<std::string>& dynamicMenuPoints, const bool isEscapeable, 
    const std::function <void(std::stringstream&)>& staticMenuFn, 
    const std::function <void(std::stringstream&, const int)>& dynamicMenuFn) {

    // Call the pre-menu callback function, if it is provided
    int numberOfMenuPoints = (int)(dynamicMenuPoints.size() - 1);
    // TODO: ezzel kell meghivni majd:    
    // std::min(numberOfMenuPoints, 0);

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
            selectedMenuPoint = ESCAPE;
            return;
        }
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
    }

    {
        std::vector <std::string> staticMenuLines = {
            "Now choose a class!"
        };
        // List of menu points
        auto& roles = ResourceParser::getInstance().getParsedRoles();
        std::vector <std::string> dynamicMenuPoints;

        for (auto& role : roles) {
            dynamicMenuPoints.push_back(role.getRoleName());
        }

        // Move so we dont have to copy
        int selectedMenuPoint = 0;
        menuGenerator(selectedMenuPoint, staticMenuLines, std::move(dynamicMenuPoints), false);
        return Player(name, isMale, roles[selectedMenuPoint]);
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

    int selectedMenuPoint = 0;
    menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, false);

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
            sellMenu(player);
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
            ss << std::endl << "------------------------------------" << std::endl;
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
            std::cout << "Not enough money." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void Menu::sellMenu(Player& player)
{
}

int Menu::restMenu(Player& player)
{
    int selectedMenuPoint = 0;

    auto getStaticPlayerGold = [player](std::stringstream& ss) ->void {
        // Build string stream object
        ss << std::endl << "Gold: " << player.getGold() << std::endl;
    };

    auto getDynamicDescription = [](std::stringstream& ss, const int& selectedMenuPoint) ->void {
        // Build string stream object
        ss << std::endl << "------------------------------------" << std::endl;
        ss << std::endl << "Costs: ";
        switch (selectedMenuPoint) {
        case 0:
            ss << "0";
            break;
        case 1:
            ss << "0";
            break;
        case 2:
            ss << "4";
            break;
        case 3:
            ss << "6";
            break;
        }
        ss << " gold." << std::endl;

        switch (selectedMenuPoint) {
        case 0:
            ss << "Restores half of your missing hp and stamina. Chance to get attacked by animals.";
            break;
        case 1:
            ss << "Restores half of your missing hp and stamina. Chance to get mugged.";
            break;
        case 2:
            ss << "Restores your hp and stamina to full.";
            break;
        case 3:
            ss << "Restores your hp and stamina to full. Enchances some stats for the next fight.";
            break;
        }
    };

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "REST"
        };

        std::vector <std::string> dynamicMenuPoints = {
            "Sleep in the bushes.",
            "Sleep on the street.",
            "Sleep in a shared room at an Inn.",
            "Sleep in a private room at an Inn."
        };
        if ((int)dynamicMenuPoints.size() == 0) {
            selectedMenuPoint = -1; // indicating error for menugenerator
        }
        menuGenerator(selectedMenuPoint, staticMenuLines, dynamicMenuPoints, true, getStaticPlayerGold, getDynamicDescription);

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
    int selectedMenuPoint = 0;

    while (1) {
        auto getStaticPlayerInfo = [player](std::stringstream& ss) ->void {
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

            ss << "------------------------------------" << std::endl;
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
    // List already equipped items

    // List inventory.

    // Player can choose between both, when enter is hit then the items equipment status changes


    int selectedMenuPoint = 0;

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
            dynamicMenuPoints.emplace_back(item.getName());
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
            std::vector<roleName> roles = itemList[selectedMenuPoint].getRoles();

            for (auto& roleName : roles) {
                ss << roleName;
                if (roleName == roles[roles.size() - 1]) {
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
    // List already equipped items

    // List inventory.

    // Player can choose between both, when enter is hit then the items equipment status changes


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
            std::vector<roleName> roles = itemList[selectedMenuPoint].getRoles();

            for (auto roleIndex = 0; roleIndex < roles.size(); roleIndex++) {
                ss << roles[roleIndex];
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
