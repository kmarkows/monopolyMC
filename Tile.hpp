#pragma once

#include <string>
#include <vector>

// TO DO divide Tile class into child classes of types Neutral, Property, Railroad, Utilities

class Tile
{
  public:
    Tile() = default;
    Tile(const std::string givenType, const int givenCost, const std::vector<int> givenRents, const int givenHouseCost,
         const uint8_t givenTileId)
        : type(givenType), cost(givenCost), rents{givenRents}, houseCost{givenHouseCost}, tileId{givenTileId} {};

    const std::string &getType() const;
    const uint8_t getId() const;
    const uint8_t getOwnerId() const;
    const int getCost() const;
    const int getHouseCost() const;
    const std::vector<int> &getRents() const;
    const uint8_t getNumOfHouses() const;

    void setOwnerId(const uint8_t toBeOwnerId);
    void buildHouse();
    void setNumOfHouses(const uint8_t newNumOfHouses);

  private:
    std::string type{};
    std::vector<int> rents{};
    int houseCost{0};
    uint8_t numOfHouses{0};
    uint8_t tileId;
    uint8_t ownerId{0};
    int cost{0};
};