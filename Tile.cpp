#include "Tile.hpp"

const std::string Tile::getType() const
{
	return type;
}

const uint8_t Tile::getId() const
{
	return tileId;
}

const uint8_t Tile::getOwnerId() const
{
	return ownerId;
}

const int Tile::getCost() const
{
	return cost;
}

void Tile::setOwnerId(const uint8_t toBeOwnerId)
{
	ownerId = toBeOwnerId;
}