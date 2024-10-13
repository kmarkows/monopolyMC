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

    void setNextCardIdToBePlayed(const uint8_t givenNextCardIdToBePlayed);
    void setIsGetOutOfPrisonCardAvailable(const uint8_t givenIsGetOutOfPrisonCardAvailable);

    const Card &getCardById(const uint8_t id) const;
    const uint8_t getNextCardIdToBePlayed() const;
    const bool getIsGetOutOfPrisonCardAvailable() const;

  private:
    void handleUtility(Game &game, Player &currPlayer, const DiceThrower *diceThrower,
                       const uint8_t utilityTileId) const;
    void handleRailroad(Game &game, Player &currPlayer, const uint8_t railroadTileId) const;

    uint8_t nextCardIdToBePlayed{0};
    bool isGetOutOfPrisonCardAvailable{true};
    std::array<Card, chanceCardsNumber> cards;
};
