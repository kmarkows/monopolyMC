#include "Game.hpp"
#include <cinttypes>
#include <cstdlib>
#include <iostream>

#include "./ut/mocks/MockDiceThrower.hpp"
#include "./ut/mocks/MockDiceThrowerSingle.hpp"

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
    Game game(200, 2, &diceThrower, &diceThrowerSingle);
    game.enableBuying();
    // game.printPlayersData();

    game.play();

    // game.printTilesVisitedCounters();

    return 0;
}