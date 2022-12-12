#include "Menu.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
#define ENTER '\r'

std::stringstream getStaticClassQuestion(const void* playerVoid) {
    // Build string stream object
    std::stringstream ss;
    ss << "\033c";
    ss << "Now choose a class!" << std::endl;
    ss << "---------" << std::endl;

    return ss;
}


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




void getStaticPlayerInfo( std::stringstream& ss, const void* playerVoid ) {
    // Build string stream object
    Player player = *(Player*)playerVoid;
    ss << std::endl;
    ss << "Name: " << player.getName() << std::endl;
    ss << "Class: " << player.getRoleName() << std::endl;
    ss << "Level: " << player.getLevel() << std::endl;
    ss << "Exp: " << player.getExp() << "/" << player.getExpNext() << std::endl;
    ss << "HP: " << player.getHp() << "/" << player.getHpMax() << std::endl;
    ss << "Attack:  " << player.getDamageMax() << std::endl;
    ss << "Defence: " << player.getDefence() << std::endl;
    ss << "Stamina: " << player.getStamina() << "/" << player.getStaminaMax() << std::endl << std::endl;

    ss << "------------------------------------" << std::endl << std::endl;

    ss << "INVENTORY" << std::endl << std::endl;

    ss << "Gold: " << player.getGold() << std::endl << std::endl;

}

int Menu::menuGenerator(const std::vector<std::string>& staticMenuLines, const std::vector<std::string>& dynamiMenuPoints, 
    const bool isEscapeable, void(*staticMenuFn)(std::stringstream&, const void*), const Player* player) {

    // Call the pre-menu callback function, if it is provided
    int numberOfMenuPoints = (int)(dynamiMenuPoints.size() - 1);
    int selectedMenuPoint = 0;

    while (1)
    {
        std::stringstream ss;
        ss << "\033c";
        for (auto line: staticMenuLines)
        {
            ss << line << std::endl;
        }
        if (staticMenuFn) {
            staticMenuFn(ss, player);
        }
        ss << std::endl;

        for (auto index = 0; index < dynamiMenuPoints.size(); index++)
        {
            if (index == selectedMenuPoint) {
                ss << "> ";
            }
            else {
                ss << "  ";
            }
            ss << dynamiMenuPoints[index] << std::endl;
        }

        if (isEscapeable)
            ss << std::endl << "Return with ESC." << std::endl;

        std::cout << ss.str();
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
        std::vector <std::string> dynamiMenuPoints = {
            "Male",
            "Female"
        };

        auto selectedMenuPoint = menuGenerator(staticMenuLines, dynamiMenuPoints, false);
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
        std::vector <std::string> dynamiMenuPoints = {
          "Warrior",
          "Mage",
          "Rouge",
          "Ranger"
        };

        auto selectedMenuPoint = (Role)menuGenerator(staticMenuLines, dynamiMenuPoints, false);
        switch (selectedMenuPoint) {
        case Role::Warrior:
            return Player(name, isMale, Role::Warrior, "Warrior");

        case Role::Mage:
            return Player(name, isMale, Role::Mage, "Mage");

        case Role::Rouge:
            return Player(name, isMale, Role::Rouge, "Rouge");

        case Role::Ranger:
            return Player(name, isMale, Role::Ranger, "Ranger");

        default:
            return Player(name, isMale, selectedMenuPoint, "Acolyte");
        }
    }
    // Do not return with std::move as it prohibits copy elision.
}

int Menu::mainMenu()
{
    std::vector <std::string> staticMenuLines = {
        "MAIN MENU"
    };
    // List of menu points
    std::vector <std::string> dynamiMenuPoints = {
      "Travel",
      "Shop",
      "Rest",
      "Player sheet",
      "Quit",
    };

    auto selectedMenuPoint = menuGenerator(staticMenuLines, dynamiMenuPoints, false);

    return selectedMenuPoint;
}

void Menu::travelMenu(Player& player)
{
}

void Menu::shopMenu(Player& player)
{
    int selectedMenuPoint;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "SHOP"
        };

        std::vector <std::string> dynamiMenuPoints = {
            "Buy",
            "Sell"
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamiMenuPoints, true);

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

void getStaticPlayerGold( std::stringstream& ss, const void* playerVoid ) {
    // Build string stream object
    Player player = *(Player*)playerVoid;
    ss << std::endl << "Gold: " << player.getGold() << std::endl;
}

void Menu::buyMenu(Player& player)
{

    int selectedMenuPoint;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "BUY"
        };

        std::vector <std::string> dynamiMenuPoints = {
            "Health potion: \t costs 3 gold, restores your hp to full.",
            "Stamina potion: \t costs 1 gold, restores your stamina to full.",
            "Sword: \t costs 10 gold, wielding this your attack damage increases by 3.",
            "Armor: \t costs 8 gold, equiping this increases your defence skill by 2."
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamiMenuPoints, true, getStaticPlayerGold, &player);

        switch (selectedMenuPoint) {
        case 0:
            if (player.getGold() >= 3) {
                player.setGold(player.getGold() - 3);
                player.setHp(player.getHpMax());
            }
            else {
                std::cout << "Not enough money." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        case 1:
            break;
        case 2:
            if (player.getGold() >= 10) {
                player.setGold(player.getGold() - 10);
                player.setDamage(player.getDamageMax() + 3);
            }
            else {
                std::cout << "Not enough money." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        case 3:
            if (player.getGold() >= 8) {
                player.setGold(player.getGold() - 8);
                player.setDefence(player.getDefence() + 2);
            }
            else {
                std::cout << "Not enough money." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        case ESCAPE:
            return;
        default:
            break;
        }
    }
}

void Menu::sellMenu(Player& player)
{
}

int Menu::restMenu(Player& player)
{
    int selectedMenuPoint;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "REST"
        };

        std::vector <std::string> dynamiMenuPoints = {
            "Sleep in the bushes: \t does not cost any gold, restores half of your missing hp and stamina. Chance to get attacked by animals.",
            "Sleep on the street: \t does not cost any gold, restores half of your missing hp and stamina. Chance to get mugged.",
            "Sleep in a shared room at an Inn: \t costs 4 gold, restores your hp and stamina to full.",
            "Sleep in a private room at an Inn: \t costs 6 gold, restores your hp and stamina to full. Enchances some stats for the next fight."
        };

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamiMenuPoints, true, getStaticPlayerGold, &player);

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
            }
            else {
                std::cout << "Not enough money." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        case ESCAPE:
            return ESCAPE;
        default:
            break;
        }
    }
}

void Menu::playerSheetMenu(Player& player)
{
    int selectedMenuPoint;

    while (1) {
        // List of menu points
        std::vector <std::string> staticMenuLines = {
            "PLAYER SHEET"
        };

        std::vector <std::string> dynamiMenuPoints = {
            "Equip / Unequip items"
        };
        if (player.getExp() >= player.getExpNext()) {
            dynamiMenuPoints.push_back("Level up");
        }

        selectedMenuPoint = menuGenerator(staticMenuLines, dynamiMenuPoints, true, getStaticPlayerInfo , &player);

        switch (selectedMenuPoint) {
        case 0:
            equipment(player);
            break;
        case 1:
            levelUp(player);
            break;
        case ESCAPE:
            return;
        default:
            break;
        }
    }
}

void Menu::equipment(Player& player)
{
}

void Menu::levelUp(Player& player)
{
    player.levelUp();
}
