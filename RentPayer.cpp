#include "RentPayer.hpp"

void RentPayer::payRent(Player &player, Player &owner, const Tile &tile, const uint8_t diceResult)
{
    if (tile.getType() == "Property")
    {
        payPropertyRent(player, owner, tile);
    }
    else if (tile.getType() == "Railroad")
    {
        payRailroadyRent(player, owner, tile);
    }
    else if (tile.getType() == "Utilities")
    {
        payUtilitiesRent(player, owner, tile, diceResult);
    }
}

void RentPayer::payPropertyRent(Player &player, Player &owner, const Tile &tile)
{
    const auto &rents = tile.getRents();
    const uint8_t numberOfHouses = tile.getNumOfHouses();
    const int rentToPay = rents.at(numberOfHouses);
    player.subtractBalance(rentToPay);
    owner.addBalance(rentToPay);
}

void RentPayer::payRailroadyRent(Player &player, Player &owner, const Tile &tile)
{
    const auto &rents = tile.getRents();
    const uint8_t numOfRailroadsOwned = utils.getNumOfTilesOfEachTypeOwnedByPlayer(owner, tile);
    const int rentToPay = rents.at(numOfRailroadsOwned - 1);
    player.subtractBalance(rentToPay);
    owner.addBalance(rentToPay);
}

void RentPayer::payUtilitiesRent(Player &player, Player &owner, const Tile &tile, const uint8_t diceResult)
{
    const auto &rents = tile.getRents();
    const uint8_t numOfUtilitiesOwned = utils.getNumOfTilesOfEachTypeOwnedByPlayer(owner, tile);
    const int rentToPay = rents.at(numOfUtilitiesOwned - 1);
    player.subtractBalance(rentToPay * diceResult);
    owner.addBalance(rentToPay * diceResult);
}