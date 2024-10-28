#include "Utils.hpp"

Player &Utils::getPlayerByIdForManipulation(std::vector<Player> &players, const uint8_t playerId) const
{
    // TO DO not finding player functionality
    for (auto &player : players)
    {
        if (player.getId() == playerId)
        {
            return player;
        }
    }
    std::cout << "Player with id:" << (int)playerId << " not found" << std::endl;
    return players.at(0);
}

const Player &Utils::getPlayerById(const std::vector<Player> &players, const uint8_t playerId) const
{
    // TO DO not finding player functionality
    for (const auto &player : players)
    {
        if (player.getId() == playerId)
        {
            return player;
        }
    }
    std::cout << "Player with id:" << (int)playerId << " not found" << std::endl;
    return players.at(0);
}

const int8_t Utils::getNumOfTilesOfGivenTypeMissingByPlayer(const Player &player, const Tile &tile) const
{
    if (tile.getType() == "Railroad")
    {
        return totalNumberOfRailroadTiles - countRailroadTiles(player);
    }
    else if (tile.getType() == "Utilities")
    {
        return totalNumberOfUtilityTiles - countUtilityTiles(player);
    }
    else if (tile.getType() == "Property")
    {
        return countMissingPropertyTiles(player, tile);
    }
    return 0;
}

const std::vector<uint8_t> Utils::getTileIdsOfGivenTypeMissingByPlayer(const Player &player, const Tile &tile) const
{
    std::vector<uint8_t> tileIdsMissingByPlayer{};
    if (tile.getType() == "Railroad")
    {
        getTileIdsOfRailroadsMissingByPlayer(player, tileIdsMissingByPlayer);
    }
    else if (tile.getType() == "Utilities")
    {
        getTileIdsOfUtilitiesMissingByPlayer(player, tileIdsMissingByPlayer);
    }
    else if (tile.getType() == "Property")
    {
        getTileIdsOfPropertiesMissingByPlayer(player, tile, tileIdsMissingByPlayer);
    }
    return tileIdsMissingByPlayer;
}

const uint8_t Utils::getNumOfTilesOfEachTypeOwnedByPlayer(const Player &player, const Tile &tile) const
{
    if (tile.getType() == "Railroad")
    {
        return countRailroadTiles(player);
    }

    else if (tile.getType() == "Utilities")
    {
        return countUtilityTiles(player);
    }

    else if (tile.getType() == "Property")
    {
        return countPropertyTiles(player, tile);
    }

    return 0;
}

const std::vector<std::vector<uint8_t>> Utils::getTileIdsOnWhichPlayerCanBuildHouses(const Player &player,
                                                                                     const Board &board) const
{
    std::vector<std::vector<uint8_t>> tileIdsOnWhichPlayerCanBuild{};
    for (const uint8_t ownedTileId : player.getOwnedTilesIds())
    {
        if (board.getTiles().at(ownedTileId).getType() == "Property")
        {
            if (ownedTileId == 1)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, brownColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 6)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, lightBlueColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 11)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, pinkColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 16)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, orangeColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 21)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, redColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 26)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, yelowColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 31)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, greenColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
            else if (ownedTileId == 37)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, blueColorTileIds, tileIdsOnWhichPlayerCanBuild);
            }
        }
    }
    return tileIdsOnWhichPlayerCanBuild;
}

const uint8_t Utils::getMaxNumOfHousesThatCanBeBuildOnGivenTile(const Tile &tile, const Board &board) const
{
    if (tile.getId() > 0 and tile.getId() < 5)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, brownColorTileIds) + 1;
    }
    else if (tile.getId() > 5 and tile.getId() < 10)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, lightBlueColorTileIds) + 1;
    }
    else if (tile.getId() > 10 and tile.getId() < 15)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, pinkColorTileIds) + 1;
    }
    else if (tile.getId() > 15 and tile.getId() < 20)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, orangeColorTileIds) + 1;
    }
    else if (tile.getId() > 20 and tile.getId() < 25)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, redColorTileIds) + 1;
    }
    else if (tile.getId() > 25 and tile.getId() < 30)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, yelowColorTileIds) + 1;
    }
    else if (tile.getId() > 30 and tile.getId() < 35)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, greenColorTileIds) + 1;
    }
    else if (tile.getId() > 35 and tile.getId() < 40)
    {
        return getMinNumberOfHousesOnSameColorTiles(board, blueColorTileIds) + 1;
    }
    return 0;
}

const bool Utils::isChanceTile(const Tile &tile) const
{
    return tile.getType() == "Chance";
}

const bool Utils::isCommunityChestTile(const Tile &tile) const
{
    return tile.getType() == "CommunityChest";
}

const bool Utils::isIncomeTax(const Tile &tile) const
{
    return tile.getType() == "IncomeTax";
}

const bool Utils::isLuxuryTax(const Tile &tile) const
{
    return tile.getType() == "LuxuryTax";
}

const uint8_t Utils::countRailroadTiles(const Player &player) const
{
    uint8_t numOfRailroadTilesOwned = 0;
    for (const auto tileId : player.getOwnedTilesIds())
    {
        if (tileId == 5 or tileId == 15 or tileId == 25 or tileId == 35)
        {
            numOfRailroadTilesOwned++;
        }
    }
    return numOfRailroadTilesOwned;
}

const uint8_t Utils::countUtilityTiles(const Player &player) const
{
    uint8_t numOfUtilityTilesOwned = 0;
    for (const auto tileId : player.getOwnedTilesIds())
    {
        if (tileId == 12 or tileId == 28)
        {
            numOfUtilityTilesOwned++;
        }
    }
    return numOfUtilityTilesOwned;
}

const uint8_t Utils::countPropertyTiles(const Player &player, const Tile &tile) const
{
    if (tile.getId() > 0 and tile.getId() < 5)
    {
        return countSameColorPropertyTiles(player, brownColorTileIds);
    }
    else if (tile.getId() > 5 and tile.getId() < 10)
    {
        return countSameColorPropertyTiles(player, lightBlueColorTileIds);
    }
    else if (tile.getId() > 10 and tile.getId() < 15)
    {
        return countSameColorPropertyTiles(player, pinkColorTileIds);
    }
    else if (tile.getId() > 15 and tile.getId() < 20)
    {
        return countSameColorPropertyTiles(player, orangeColorTileIds);
    }
    else if (tile.getId() > 20 and tile.getId() < 25)
    {
        return countSameColorPropertyTiles(player, redColorTileIds);
    }
    else if (tile.getId() > 25 and tile.getId() < 30)
    {
        return countSameColorPropertyTiles(player, yelowColorTileIds);
    }
    else if (tile.getId() > 30 and tile.getId() < 35)
    {
        return countSameColorPropertyTiles(player, greenColorTileIds);
    }
    else if (tile.getId() > 35 and tile.getId() < 40)
    {
        return countSameColorPropertyTiles(player, blueColorTileIds);
    }
    return 0;
}

const int8_t Utils::countMissingPropertyTiles(const Player &player, const Tile &tile) const
{
    if (tile.getId() > 0 and tile.getId() < 5)
    {
        return brownColorTileIds.size() - countSameColorPropertyTiles(player, brownColorTileIds);
    }
    else if (tile.getId() > 5 and tile.getId() < 10)
    {
        return lightBlueColorTileIds.size() - countSameColorPropertyTiles(player, lightBlueColorTileIds);
    }
    else if (tile.getId() > 10 and tile.getId() < 15)
    {
        return pinkColorTileIds.size() - countSameColorPropertyTiles(player, pinkColorTileIds);
    }
    else if (tile.getId() > 15 and tile.getId() < 20)
    {
        return orangeColorTileIds.size() - countSameColorPropertyTiles(player, orangeColorTileIds);
    }
    else if (tile.getId() > 20 and tile.getId() < 25)
    {
        return redColorTileIds.size() - countSameColorPropertyTiles(player, redColorTileIds);
    }
    else if (tile.getId() > 25 and tile.getId() < 30)
    {
        return yelowColorTileIds.size() - countSameColorPropertyTiles(player, yelowColorTileIds);
    }
    else if (tile.getId() > 30 and tile.getId() < 35)
    {
        return greenColorTileIds.size() - countSameColorPropertyTiles(player, greenColorTileIds);
    }
    else if (tile.getId() > 35 and tile.getId() < 40)
    {
        return blueColorTileIds.size() - countSameColorPropertyTiles(player, blueColorTileIds);
    }
    return 0;
}

const uint8_t Utils::countSameColorPropertyTiles(const Player &player, const std::vector<uint8_t> &sameColorTiles) const
{
    uint8_t numOfGivenColorTilesOwned = 0;
    for (const auto tileId : player.getOwnedTilesIds())
    {
        for (const auto givenColorId : sameColorTiles)
        {
            if (givenColorId == tileId)
            {
                numOfGivenColorTilesOwned++;
            }
        }
    }
    return numOfGivenColorTilesOwned;
}

void Utils::checkIfBuildingPossibleOnGivenColorTiles(
    const Player &player, const std::vector<uint8_t> &sameColorTiles,
    std::vector<std::vector<uint8_t>> &tileIdsOnWhichPlayerCanBuild) const
{
    if (sameColorTiles.size() == countSameColorPropertyTiles(player, sameColorTiles))
    {
        tileIdsOnWhichPlayerCanBuild.push_back(sameColorTiles);
    }
}

const uint8_t Utils::getMinNumberOfHousesOnSameColorTiles(const Board &board,
                                                          const std::vector<uint8_t> &sameColorTiles) const
{
    uint8_t minNumberOfHouses{6};
    for (const uint8_t sameColorId : sameColorTiles)
    {
        minNumberOfHouses = std::min(board.getTiles().at(sameColorId).getNumOfHouses(), minNumberOfHouses);
    }
    return minNumberOfHouses;
}

void Utils::getTileIdsOfRailroadsMissingByPlayer(const Player &player,
                                                 std::vector<uint8_t> &tileIdsMissingByPlayer) const
{
    for (const uint8_t railroadTileId : railroadTileIds)
    {
        const auto &ownedTileIds = player.getOwnedTilesIds();
        if (std::find(ownedTileIds.begin(), ownedTileIds.end(), railroadTileId) == std::end(ownedTileIds))
        {
            tileIdsMissingByPlayer.push_back(railroadTileId);
        }
    }
}

void Utils::getTileIdsOfUtilitiesMissingByPlayer(const Player &player,
                                                 std::vector<uint8_t> &tileIdsMissingByPlayer) const
{
    for (const uint8_t utilitiesTileId : utilitiesTileIds)
    {
        const auto &ownedTileIds = player.getOwnedTilesIds();
        if (std::find(ownedTileIds.begin(), ownedTileIds.end(), utilitiesTileId) == std::end(ownedTileIds))
        {
            tileIdsMissingByPlayer.push_back(utilitiesTileId);
        }
    }
}

void Utils::getTileIdsOfPropertiesMissingByPlayer(const Player &player, const Tile &tile,
                                                  std::vector<uint8_t> &tileIdsMissingByPlayer) const
{
    if (tile.getId() > 0 and tile.getId() < 5)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, brownColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 5 and tile.getId() < 10)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, lightBlueColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 10 and tile.getId() < 15)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, pinkColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 15 and tile.getId() < 20)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, orangeColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 20 and tile.getId() < 25)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, redColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 25 and tile.getId() < 30)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, yelowColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 30 and tile.getId() < 35)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, greenColorTileIds, tileIdsMissingByPlayer);
    }
    else if (tile.getId() > 35 and tile.getId() < 40)
    {
        getTileIdsOfPropertiesMissingByPlayerOfEachColor(player, blueColorTileIds, tileIdsMissingByPlayer);
    }
}

void Utils::getTileIdsOfPropertiesMissingByPlayerOfEachColor(const Player &player,
                                                             const std::vector<uint8_t> &brownColorTileIds,
                                                             std::vector<uint8_t> &tileIdsMissingByPlayer) const
{
    for (const uint8_t brownColorTileId : brownColorTileIds)
    {
        const auto &ownedTileIds = player.getOwnedTilesIds();
        if (std::find(ownedTileIds.begin(), ownedTileIds.end(), brownColorTileId) == std::end(ownedTileIds))
        {
            tileIdsMissingByPlayer.push_back(brownColorTileId);
        }
    }
}
