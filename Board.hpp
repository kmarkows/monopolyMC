#pragma once

#include <array>
#include <iostream>

#include "Tile.hpp"

constexpr uint8_t numOfMonopolyBoradTiles = 40;
constexpr uint8_t goToPrisonTile = 30;
constexpr uint8_t prisonTile = 10;

class Board
{
  public:
    Board();

    const std::array<Tile, numOfMonopolyBoradTiles> &getTiles() const;
    std::array<Tile, numOfMonopolyBoradTiles> &getTilesForModification();

  private:
    std::array<Tile, numOfMonopolyBoradTiles> tiles{};
};