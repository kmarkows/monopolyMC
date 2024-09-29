#pragma once

#include "Card.hpp"

constexpr uint8_t chanceCardsNumber = 15;

class Chance
{
  public:
    Chance();
    const Card &getCardById(const uint8_t id) const;

  private:
    void handleUtility(Game &game, Player &currPlayer, const DiceThrower *diceThrower,
                       const uint8_t utilityTileId) const;
    void handleRailroad(Game &game, Player &currPlayer, const uint8_t railroadTileId) const;

    std::array<Card, chanceCardsNumber> cards;
};
