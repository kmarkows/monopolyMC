#include "Game.hpp"

#include <chrono>
#include <cinttypes>
#include <cstdlib>
#include <iostream>

int main()
{
    srand((unsigned)time(NULL));
    // Player player1(0);
    // player1.print();
    // const auto diceResult = player1.throwDice();
    // std::cout << (int)diceResult.getFirst() << " " <<
    // (int)diceResult.getSecond() << std::endl;

    DiceThrower diceThrower;
    DiceThrowerSingle diceThrowerSingle;
    Game game(1000, 8, &diceThrower, &diceThrowerSingle);
    game.enableTilesTrading();
    game.enableTilesBuying();
    game.enableHousesBuying();
    game.enableCards();
    game.enablePaying();
    // game.printPlayersData();

    auto start = std::chrono::high_resolution_clock::now();
    for (uint16_t i = 0; i < 1; i++)
    {
        game.play();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time:" << duration.count() << "s\n";

    // game.printTilesVisitedCounters();

    return 0;
}