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

void printP(Player& player) {
    std::cout << "\033c";
    std::cout << "STATISTIS" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "Name: " << player.getName() << std::endl;
    std::cout << "Level: " << player.getLevel() << std::endl;
    std::cout << "Exp: " << player.getExp() << "/" << player.getExpNext() << std::endl;
    std::cout << "HP: " << player.getHp() << "/" << player.getHpMax() << std::endl;
    std::cout << "Attack:  " << player.getDamageMax() << std::endl;
    std::cout << "Defence: " << player.getDefence() << std::endl;
    std::cout << "Stamina: " << player.getStamina() << "/" << player.getStaminaMax() << std::endl;
    std::cout << "------------------" << std::endl;

    std::cout << "INVENTORY" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "Gold: " << player.getGold() << std::endl;

    std::cout << "------------------" << std::endl;
}

void Menu::printPlayer(Player& player)
{
    int numberOfMenuPoints = 0;
    printP(player);
    std::cout << "> Equip / Unequip items" << std::endl;
    if (player.getExp() >= player.getExpNext()) {
        std::cout << "  Level up" << std::endl;
        numberOfMenuPoints++;
    }
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
                player.setLevel(player.getLevel() + 1);
                player.setExp(player.getExp() - player.getExpNext());
                player.setExpNext(player.getExpNext() * 2);
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
        printP(player);
        switch (selectedMenuPoint) {
        case 0:
            std::cout << "> Equip / Unequip items" << std::endl;
            if (player.getExp() >= player.getExpNext()) {
                std::cout << "  Level up" << std::endl;
            }
            break;
        case 1:
            selectedMenuPoint = std::min(selectedMenuPoint++, numberOfMenuPoints);
            std::cout << "  Equip / Unequip items" << std::endl;
            if (player.getExp() >= player.getExpNext()) {
                std::cout << "> Level up" << std::endl;
            }
            break;
        default:
            break;
        }
    }



    std::cout << "Return with ESC.";
    _getch();
}

void Menu::equipment(Player& player)
{
}

void Menu::levelUp(Player& player)
{

}
