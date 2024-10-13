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
    void buildHouses(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils);
    void buildHotels(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils);

    int moneyToSpentAtHouseBuying{0};
    int8_t availableHouses{32};
    int8_t availablHotels{12};
};