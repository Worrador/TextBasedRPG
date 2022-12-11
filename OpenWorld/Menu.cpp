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

std::stringstream getStaticPlayerInfo(Player& player) {
    // Build string stream object
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

void Menu::playerMenu(Player& player)
{


    int numberOfMenuPoints = 0;
    auto ss = getStaticPlayerInfo(player);

    ss << "> Equip / Unequip items" << std::endl;
    if (player.getExp() >= player.getExpNext()) {
        ss << "  Level up" << std::endl;
        numberOfMenuPoints++;
    }
    ss << std::endl << "Return with ESC.";
    std::cout << ss.str();
    int selectedMenuPoint = 0;
    while (1)
    {
        switch ((_getch())) {
        case KEY_UP:
            selectedMenuPoint = std::min(selectedMenuPoint--, 0);
            break;
        case KEY_DOWN:
            selectedMenuPoint = std::max(selectedMenuPoint++, numberOfMenuPoints);
            break;
        case ENTER:
            switch (selectedMenuPoint) {
            case 0:
                equipment(player);
                break;
            case 1:
                levelUp(player);
                if (player.getExp() < player.getExpNext()) {
                    numberOfMenuPoints--;
                    selectedMenuPoint--;
                }
                break;
            default:
                break;
            }
            break;
        case ESCAPE:
            return;
        default:
            break;
        }
        ss = getStaticPlayerInfo(player);
        switch (selectedMenuPoint) {
        case 0:
            ss << "> Equip / Unequip items" << std::endl;
            if (player.getExp() >= player.getExpNext()) {
                ss << "  Level up" << std::endl;
            }
            break;
        case 1:
            selectedMenuPoint = std::min(selectedMenuPoint++, numberOfMenuPoints);
            ss << "  Equip / Unequip items" << std::endl;
            if (player.getExp() >= player.getExpNext()) {
                ss << "> Level up" << std::endl;
            }
            break;
        default:
            break;
        }

        ss << std::endl << "Return with ESC.";
        std::cout << ss.str();
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
