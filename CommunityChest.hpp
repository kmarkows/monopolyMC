#pragma once

#include "Card.hpp"
#include "Game.fwd.hpp"

constexpr uint8_t communityChestCardsNumber = 17;

class CommunityChest
{
  public:
    CommunityChest();
    void playNextCard(Game &game, Player &player, const DiceThrower *diceThrower);
    const Card &getCardById(const uint8_t id) const;

  private:
    uint8_t nextCardIdToBePlayed{0};
    std::array<Card, communityChestCardsNumber> cards;
};
