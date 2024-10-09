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

    void logHouseBuying(const Player &player, const Tile &tile);
    void logTileBuying(const Player &player, const Tile &tile);

  private:
    std::ofstream logFile;
};