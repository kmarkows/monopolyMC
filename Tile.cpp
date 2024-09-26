#include "Tile.hpp"

const std::string &Tile::getType() const
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

const std::vector<int> &Tile::getRents() const
{
    return rents;
}

const uint8_t Tile::getNumOfHouses() const
{
    return numOfHouses;
}

void Tile::setOwnerId(const uint8_t toBeOwnerId)
{
    ownerId = toBeOwnerId;
}

void Tile::buildHouse()
{
    numOfHouses++;
}

void Tile::setNumOfHouses(const uint8_t newNumOfHouses)
{
    numOfHouses = newNumOfHouses;
}