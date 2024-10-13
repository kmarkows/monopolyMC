#pragma once

#include "Player.hpp"
#include "Tile.hpp"

#include <fstream>
#include <iostream>
#include <string>

class Logger
{
  public:
    Logger(const std::string &fileName);
    ~Logger();

    void logStartOfEachIteration(const std::vector<Player> &players, const uint32_t iteration);
    void logTileBuying(const Player &player, const Tile &tile);
    void logTryHouseBuying(const Player &player);
    void logHouseBuying(const Player &player, const Tile &tile);

    void logPlayerGoesToPrison(const Player &player);
    void logPlayerTriesToGetOutOfPrison(const Player &player);
    void logPlayerGetsOutOfPrisonByCard(const Player &player, const DiceResult &diceResult);
    void logPlayerGetsOutOfPrisonByFine(const Player &player, const DiceResult &diceResult);
    void logPlayerGetsOutOfPrisonByDouble(const Player &player, const DiceResult &diceResult);
    void logPlayerGetsOutOfPrisonByStaying(const Player &player, const DiceResult &diceResult);

    void logDrawCardCommunityChest(const Player &player, const uint8_t cardToBeDrawed);
    void logDrawCardChance(const Player &player, const uint8_t cardToBeDrawed);

    void logRentPayer(const Player &player, const Player &owner, const Tile &tile);
    void logPayingRent(const Player &player, const Player &owner, const int rent);

    void logRemovePlayer(const Player &player);
    void logGameEnd(const std::vector<Player> &players);

  private:
    std::ofstream logFile;
};