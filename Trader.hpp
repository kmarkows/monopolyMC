#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "Utils.hpp"

#include <stack>

class Trader
{
  public:
    Trader() = default;
    void trade(Player &buyer, std::vector<Player> &players, Board &board, Utils &utils) const;

  private:
    std::array<std::vector<uint8_t>, 5> createTileIdsToBuyToMissingTilesNum(Player &buyer, Board &board,
                                                                            Utils &utils) const;
    std::stack<uint8_t> createTileIdsToBuy(const Player &buyer, const Board &board,
                                           const std::array<std::vector<uint8_t>, 5> &tileIdsToBuyToMissingTilesNum,
                                           const Utils &utils) const;
    const float calcSellingPrice(const Player &seller, const Tile &tile, const Utils &utils,
                                 const uint8_t tileId) const;
    const float calcBuyingPrice(const Player &buyer, const Tile &tile, const Utils &utils, const uint8_t tileId) const;
    void tradeTile(Player &buyer, Player &seller, Board &board, const uint8_t tileId, const int price) const;
};