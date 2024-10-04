#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "Utils.hpp"

class HousesBuilder
{
  public:
    HousesBuilder() = default;
    void tryBuilding(Player &player, Board &board, const Utils &utils);

  private:
};