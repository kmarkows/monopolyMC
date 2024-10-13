#pragma once

#include "Card.hpp"
#include "Game.fwd.hpp"

constexpr uint8_t communityChestCardsNumber = 17;

class CommunityChest
{
  public:
    CommunityChest();
    void playNextCard(Game &game, Player &player, const DiceThrower *diceThrower);

    void setNextCardIdToBePlayed(const uint8_t givenNextCardIdToBePlayed);
    void setIsGetOutOfPrisonCardAvailable(const uint8_t givenIsGetOutOfPrisonCardAvailable);

    const Card &getCardById(const uint8_t id) const;
    const uint8_t getNextCardIdToBePlayed() const;
    const bool getIsGetOutOfPrisonCardAvailable() const;

  private:
    uint8_t nextCardIdToBePlayed{0};
    bool isGetOutOfPrisonCardAvailable{true};
    std::array<Card, communityChestCardsNumber> cards;
};
