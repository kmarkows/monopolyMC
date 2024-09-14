#pragma once

#include "DiceThrower.hpp"
#include "Game.hpp"
#include "functional"

class Card
{
  public:
	Card() = default;
	Card(const std::function<void(Game &, Player &, const DiceThrower *)> givenAction, const uint8_t givenId)
		: action{givenAction}, id{givenId} {};

	void doAction(Game &game, Player &player, const DiceThrower *diceThrower) const;
	const uint8_t getId() const;

  private:
	uint8_t id;
	std::function<void(Game &, Player &, const DiceThrower *)> action;
};