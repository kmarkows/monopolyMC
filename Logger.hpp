#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "Tile.hpp"

#include <fstream>
#include <iostream>
#include <string>

class Logger
{
  public:
    Logger();
    ~Logger();

    void logStartOfEachIteration(const std::vector<Player> &players, const Board &board, const uint32_t iteration);

    void logDiceRolling(const Player &player, const DiceResult &diceResult);
    void logMovement(const Player &player);

    void logTryTileBuying(const Player &player, const Tile &tile);
    void logTileBuying(const Player &player, const Tile &tile);

    void logTryHouseBuying(const Player &player, const int8_t availableHouses, const int8_t availablHotels);
    void logHouseBuying(const Player &player, const Tile &tile, const int8_t availableHouses,
                        const int8_t availablHotels);

    void logTryTilesTrading(const Player &player);
    void logTilesTrading(const Player &player, const Player &owner, const Tile &tile, const int price);

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

    void logRemovePlayer(const Player &player, const Board &board);
    void logGameEnd(const std::vector<Player> &players);
    void playerEndsTurn();

  private:
    std::string fileName{
        "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt"};
    std::ofstream logFile;
};