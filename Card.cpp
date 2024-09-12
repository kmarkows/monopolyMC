#include "Card.hpp"

void Card::doAction(Game &game, Player &player) const
{
	action(game, player);
}

const uint8_t Card::getId() const
{
	return id;
}