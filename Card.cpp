#include "Card.hpp"

void Card::doAction(Player &player, Board &board) const
{
	action(player, board);
}

const uint8_t Card::getId() const
{
	return id;
}