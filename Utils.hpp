#pragma once

#include <vector>

#include "Board.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Utils
{
  public:
    Utils() = default;
    const uint8_t getNumOfTilesOfEachTypeOwnedByPlayer(const Player &player, const Tile &tile) const;

  private:
    const uint8_t countRailroadTiles(const Player &player) const;
    const uint8_t countUtilityTiles(const Player &player) const;
    const uint8_t countPropertyTiles(const Player &player, const Tile &tile) const;
    const uint8_t countSameColorPropertyTiles(const Player &player, const std::vector<uint8_t> sameColorTiles) const;
};
