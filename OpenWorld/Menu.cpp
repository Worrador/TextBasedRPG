#include "Menu.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
#define ENTER '\r'



std::stringstream getStaticGenderQuestion(const void* playerVoid) {
    // Build string stream object
    std::stringstream ss;
    ss << "\033c";
    ss << "What is your gender?" << std::endl;
    ss << "---------" << std::endl;

    return ss;
}

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




std::stringstream getStaticPlayerInfo( const void* playerVoid) {
    // Build string stream object
    Player player = *(Player*)playerVoid;
    std::stringstream ss;
    ss << "\033c";
    ss << "STATISTICS" << std::endl;
    ss << "-----------" << std::endl;
    ss << "Name: " << player.getName() << std::endl;
    ss << "Level: " << player.getLevel() << std::endl;
    ss << "Exp: " << player.getExp() << "/" << player.getExpNext() << std::endl;
    ss << "HP: " << player.getHp() << "/" << player.getHpMax() << std::endl;
    ss << "Attack:  " << player.getDamageMax() << std::endl;
    ss << "Defence: " << player.getDefence() << std::endl;
    ss << "Stamina: " << player.getStamina() << "/" << player.getStaminaMax() << std::endl;
    ss << "------------------" << std::endl;
    ss << "INVENTORY" << std::endl;
    ss << "---------" << std::endl;
    ss << "Gold: " << player.getGold() << std::endl;
    ss << "------------------" << std::endl;

    return ss;

}

int menuGenerator(const std::vector<std::string>& menuPoints, std::stringstream(*staticMenuFn)(const void*), const bool isEscapeable = true, const Player* player = nullptr) {
    // Call the pre-menu callback function, if it is provided
    std::stringstream ss;
    int numberOfMenuPoints = menuPoints.size() - 1;
    int selectedMenuPoint = 0;

    while (1)
    {
        if (staticMenuFn) {
            ss = staticMenuFn(player);
        }
        for (auto index = 0; index < menuPoints.size(); index++)
        {
            if (index == selectedMenuPoint) {
                ss << "> ";
            }
            else {
                ss << "  ";
            }
            ss << menuPoints[index] << std::endl;
        }

        if(isEscapeable)
            ss << std::endl << "Return with ESC.";

        std::cout << ss.str();
        switch ((_getch())) {
        case KEY_UP:
            selectedMenuPoint = std::max(--selectedMenuPoint, 0);
            break;
        case KEY_DOWN:
            selectedMenuPoint = std::min(++selectedMenuPoint, numberOfMenuPoints);
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
    std::string name;
    std::cout << "Please enter your name!" << std::endl;
    std::cout << "---------" << std::endl;

    std::cin >> name;
    std::cout << "\033c";
    std::cout << "Welcome " << name << "!" << std::endl << "This is a command line RPG game which you can play using only your keyboard." << std::endl;
    std::cout << "Let's create your character!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    bool isMale;

    {
        // List of menu points
        std::vector <std::string> menuPoints = {
            "Male",
            "Female"
        };

        auto selectedMenuPoint = menuGenerator(menuPoints, getStaticGenderQuestion, false);
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
        // List of menu points
        std::vector <std::string> menuPoints = {
          "Warrior",
          "Mage",
          "Rouge",
          "Ranger"
        };

        auto selectedMenuPoint = menuGenerator(menuPoints, getStaticClassQuestion, false);
        switch (selectedMenuPoint) {
        case Role::Warrior:
            return Player(name, isMale, 12, std::floor(3 / 2), 3, 2, 10);

        case Role::Mage:
            return Player(name, isMale, 6, std::floor(12 / 2), 12, 0, 5);

        case Role::Rouge:
            return Player(name, isMale, 9, std::floor(7 / 2), 7, 1, 7);

        case Role::Ranger:
            return Player(name, isMale, 8, std::floor(8 / 2), 8, 1, 6);

        default:
            return Player(name, isMale, 8, std::floor(7 / 2), 8, 1, 7);
        }
    }
    // Do not return with std::move as it prohibits copy elision.
}

void Menu::playerMenu(Player& player)
{
    while (1) {
        // List of menu points
        std::vector <std::string> menuPoints = {
          "Equip / Unequip items"
        };
        if (player.getExp() >= player.getExpNext()) {
            menuPoints.push_back("Level up");
        }

        auto selectedMenuPoint = menuGenerator(menuPoints, getStaticPlayerInfo, true, &player);

        switch (selectedMenuPoint) {
        case 0:
            equipment(player);
            break;
        case 1:
            levelUp(player);
            break;
        case ESCAPE:
            return;
            break;
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
    player.setLevel(player.getLevel() + 1);
    player.setExp(player.getExp() - player.getExpNext());
    player.setExpNext(player.getExpNext() * 2);
}
