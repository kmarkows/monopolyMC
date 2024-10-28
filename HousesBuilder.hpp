#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "Utils.hpp"

class HousesBuilder
{
  public:
    HousesBuilder() = default;
    void tryBuilding(Player &player, Board &board, const Utils &utils);

    void addAvailableHouses(const uint8_t availableHousesToAdd);
    const uint8_t getAvailableHouses() const;
    void setAvailableHouses(const uint8_t availableHousesToSet);

    void addAvailableHotels(const uint8_t availableHotelsToAdd);
    const uint8_t getAvailableHotels() const;
    void setAvailableHotels(const uint8_t availableHotelsToSet);

  private:
    void buildHouses(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils);
    void buildHotels(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils);

    int moneyToSpentAtHouseBuying{0};
    int8_t availableHouses{32};
    int8_t availableHotels{12};
};