#pragma once

#include "Board.hpp"
#include "Chance.hpp"
#include "CommunityChest.hpp"
#include "Player.hpp"

#include <vector>

class PlayerRemover
{
  public:
    PlayerRemover() = default;
    void remove(std::vector<Player> &players, Player &playerToRemove, Board &board, CommunityChest &communiyChest,
                Chance &chance);
};
