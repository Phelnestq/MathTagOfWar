#include <iostream>
#include <memory>
#include <cstdlib>  // for srand()
#include <ctime>    // for time()
#include "Game.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "Difficulty.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "=== Math Tug of War ===\n\n";
    std::cout << "Select difficulty:\n";
    std::cout << "  1. Primary Easy\n";
    std::cout << "  2. Primary Hard\n";
    std::cout << "  3. Secondary Easy\n";
    std::cout << "  4. Secondary Hard\n";
    std::cout << "Choice: ";

    int choice = 1;
    std::cin >> choice;

    Difficulty diff;
    switch (choice) {
        case 2:  diff = Difficulty::PRIMARY_HARD;    break;
        case 3:  diff = Difficulty::SECONDARY_EASY;  break;
        case 4:  diff = Difficulty::SECONDARY_HARD;  break;
        default: diff = Difficulty::PRIMARY_EASY;    break;
    }

    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    // Player 1 = human, Player 2 = computer
    auto human    = std::make_unique<Player>(playerName);
    auto computer = std::make_unique<ComputerPlayer>("Computer", diff);

    Game game(std::move(human), std::move(computer), diff);
    game.run();

    return 0;
}
