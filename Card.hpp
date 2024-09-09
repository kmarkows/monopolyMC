#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "functional"

class Card
{
  public:
	Card() = default;
	Card(const std::function<void(Player &, Board &)> givenAction, const uint8_t givenId)
		: action{givenAction}, id{givenId} {};

	void doAction(Player &player, Board &board) const;
	const uint8_t getId() const;

  private:
	uint8_t id;
	std::function<void(Player &, Board &)> action;
};