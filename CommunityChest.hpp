#pragma once

#include "Card.hpp"

constexpr uint8_t communityChestCardsNumber = 17;

class CommunityChest
{
  public:
    CommunityChest();
    const Card &getCardById(const uint8_t id) const;

  private:
    std::array<Card, communityChestCardsNumber> cards;
};
