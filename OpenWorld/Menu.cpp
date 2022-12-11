#include "Menu.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
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



Player Menu::playerCreationMenu()
{
    std::string name;
    std::cout << "Please enter your name!" << std::endl;
    std::cout << "---------" << std::endl;

    std::cin >> name;

    std::cout << std::endl << "What is your gender?" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "Male" << std::endl;
    std::cout << "Female" << std::endl;

    bool isMale;

    switch (getInputBetween(0, 1)) {
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


    std::cout << std::endl << "Now choose a class!" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "0: Warrior" << std::endl;
    std::cout << "1: Mage" << std::endl;
    std::cout << "2: Rouge" << std::endl;
    std::cout << "3: Ranger" << std::endl;


    int hpMax, dmg, def, sta;
    switch (getInputBetween(0, 3)) {
    case Role::Warrior:
        hpMax = 12;
        dmg = 3;
        def = 2;
        sta = 10;
        break;
    case Role::Mage:
        hpMax = 5;
        dmg = 12;
        def = 0;
        sta = 5;
        break;
    case Role::Rouge:
        hpMax = 8;
        dmg = 7;
        def = 1;
        sta = 7;
        break;
    case Role::Ranger:
        hpMax = 7;
        dmg = 8;
        def = 1;
        sta = 6;
        break;
    default:
        hpMax = 7;
        dmg = 7;
        def = 1;
        sta = 7;
        break;

    }

    // Do not return with std::move as it prohibits copy elision.
    return Player(name, isMale, hpMax, std::floor(dmg / 2), dmg, def, sta);
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

int menuGenerator(const std::vector<std::string>& menuPoints, std::stringstream(*staticMenuFn)(const void*), const Player* player = nullptr) {
    // Call the pre-menu callback function, if it is provided
    std::stringstream ss;
    int numberOfMenuPoints = menuPoints.size() - 1;
    int selectedMenuPoint = 0;

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

    ss << std::endl << "Return with ESC.";
    std::cout << ss.str();


    while (1)
    {
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
            return ESCAPE;
        default:
            break;
        }

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

        ss << std::endl << "Return with ESC.";
        std::cout << ss.str();
    }

    return 0;

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

        auto selectedMenuPoint = menuGenerator(menuPoints, getStaticPlayerInfo, &player);

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
