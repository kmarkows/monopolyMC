#pragma once

#include "Board.hpp"
#include "Player.hpp"

#include <vector>

class PlayerRemover
{
  public:
    PlayerRemover() = default;
    void remove(std::vector<Player> &players, Player &playerToRemove, Board &board);
};
