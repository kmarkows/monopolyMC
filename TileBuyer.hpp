#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "Utils.hpp"

class TileBuyer
{
  public:
    TileBuyer() = default;
    void tryBuying(Player &player, Board &board, const Utils &utils);

  private:
    void handleBuyableTile(Player &player, Tile &tile, const Utils &utils);
    void buyTile(Player &player, Tile &tile);
};