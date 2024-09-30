#pragma once

#include "Card.hpp"
#include "Game.fwd.hpp"
#include "Player.hpp"

constexpr uint8_t chanceCardsNumber = 15;

class Chance
{
  public:
    Chance();
    void playNextCard(Game &game, Player &player, const DiceThrower *diceThrower);
    const Card &getCardById(const uint8_t id) const;

  private:
    void handleUtility(Game &game, Player &currPlayer, const DiceThrower *diceThrower,
                       const uint8_t utilityTileId) const;
    void handleRailroad(Game &game, Player &currPlayer, const uint8_t railroadTileId) const;

    uint8_t nextCardIdToBePlayed{0};
    std::array<Card, chanceCardsNumber> cards;
};
