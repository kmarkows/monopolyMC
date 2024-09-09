#pragma once

#include "Card.hpp"

constexpr uint8_t chanceCardNumber = 15;

class Chance
{
  public:
	Chance();
	const Card &getCardById(const uint8_t id) const;

  private:
	std::array<Card, chanceCardNumber> cards;
};
