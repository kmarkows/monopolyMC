#include "Utils.hpp"

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

const std::vector<uint8_t> Utils::getTileIdsOnWhichPlayerCanBuildHouses(const Player &player, const Board &board) const
{
    std::unordered_set<uint8_t> tileIdsOnWhichPlayerCanBuildSet{};
    for (const uint8_t ownedTileId : player.getOwnedTilesIds())
    {
        if (board.getTiles().at(ownedTileId).getType() == "Property")
        {
            if (ownedTileId > 0 and ownedTileId < 5)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, brownColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 5 and ownedTileId < 10)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, lightBlueColorTileIds,
                                                         tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 10 and ownedTileId < 15)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, pinkColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 15 and ownedTileId < 20)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, orangeColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 20 and ownedTileId < 25)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, redColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 25 and ownedTileId < 30)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, yelowColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 30 and ownedTileId < 35)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, greenColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
            else if (ownedTileId > 35 and ownedTileId < 40)
            {
                checkIfBuildingPossibleOnGivenColorTiles(player, blueColorTileIds, tileIdsOnWhichPlayerCanBuildSet);
            }
        }
    }

    std::vector<uint8_t> tileIdsOnWhichPlayerCanBuild{};
    for (const uint8_t buildableIds : tileIdsOnWhichPlayerCanBuildSet)
    {
        tileIdsOnWhichPlayerCanBuild.push_back(buildableIds);
    }
    std::sort(tileIdsOnWhichPlayerCanBuild.begin(), tileIdsOnWhichPlayerCanBuild.end());
    return tileIdsOnWhichPlayerCanBuild;
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

void Utils::checkIfBuildingPossibleOnGivenColorTiles(const Player &player, const std::vector<uint8_t> &sameColorTiles,
                                                     std::unordered_set<uint8_t> &tileIdsOnWhichPlayerCanBuild) const
{
    if (sameColorTiles.size() == countSameColorPropertyTiles(player, sameColorTiles))
    {
        for (const uint8_t sameColorTileId : sameColorTiles)
        {
            tileIdsOnWhichPlayerCanBuild.insert(sameColorTileId);
        }
    }
}