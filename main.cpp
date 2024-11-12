#include "Game.hpp"

#include <chrono>
#include <cinttypes>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

int main()
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand(seed);

    DiceThrower diceThrower;
    std::vector<uint8_t> defaultPlayerOrder{1, 2, 3, 4, 5, 6, 7, 8};
    std::shuffle(defaultPlayerOrder.begin(), defaultPlayerOrder.end(), std::default_random_engine(seed));

    Game game(1000, 8, &diceThrower, defaultPlayerOrder);
    game.enableTilesTrading();
    game.enableTilesBuying();
    game.enableHousesBuying();
    game.enableCards();
    game.enablePaying();

    auto start = std::chrono::high_resolution_clock::now();
    game.play();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::ofstream file(
        "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/statistics/singleGameDuration.txt",
        std::ios::app);
    if (!file)
    {
        std::cout << "Error: Could not open the singleGameDuration.txt file!" << std::endl;
    }
    file << duration.count() << std::endl;
    file.close();

    return 0;
}