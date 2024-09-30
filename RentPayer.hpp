#pragma once

#include "Player.hpp"
#include "Tile.hpp"
#include "Utils.hpp"

class RentPayer
{
  public:
    RentPayer() = default;
    RentPayer(const Utils &utils) : utils(utils) {};
    void payRent(Player &player, Player &owner, const Tile &tile, const uint8_t diceResult);

  private:
    void payPropertyRent(Player &player, Player &owner, const Tile &tile);
    void payRailroadyRent(Player &player, Player &owner, const Tile &tile);
    void payUtilitiesRent(Player &player, Player &owner, const Tile &tile, const uint8_t diceResult);

    Utils utils;
};