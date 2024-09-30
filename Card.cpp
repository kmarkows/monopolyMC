#include "Card.hpp"
#include "Game.hpp"

void Card::doAction(Game &game, Player &player, const DiceThrower *diceThrower) const
{
    action(game, player, diceThrower);
}

const uint8_t Card::getId() const
{
    return id;
}