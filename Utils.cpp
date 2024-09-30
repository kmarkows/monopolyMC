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

const bool Utils::isChanceTile(const uint8_t tileId) const
{
    return tileId == 7 or tileId == 22 or tileId == 36;
}

const bool Utils::isCommunityChestTile(const uint8_t tileId) const
{
    return tileId == 2 or tileId == 17 or tileId == 23;
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
        std::vector<uint8_t> brownColorTileIds{1, 3};
        return countSameColorPropertyTiles(player, brownColorTileIds);
    }
    else if (tile.getId() > 5 and tile.getId() < 10)
    {
        std::vector<uint8_t> lightBlueColorTileIds{6, 8, 9};
        return countSameColorPropertyTiles(player, lightBlueColorTileIds);
    }
    else if (tile.getId() > 10 and tile.getId() < 15)
    {
        std::vector<uint8_t> pinkColorTileIds{11, 13, 14};
        return countSameColorPropertyTiles(player, pinkColorTileIds);
    }
    else if (tile.getId() > 15 and tile.getId() < 20)
    {
        std::vector<uint8_t> orangeColorTileIds{16, 18, 19};
        return countSameColorPropertyTiles(player, orangeColorTileIds);
    }
    else if (tile.getId() > 20 and tile.getId() < 25)
    {
        std::vector<uint8_t> redColorTileIds{21, 23, 24};
        return countSameColorPropertyTiles(player, redColorTileIds);
    }
    else if (tile.getId() > 25 and tile.getId() < 30)
    {
        std::vector<uint8_t> yelowColorTileIds{26, 27, 29};
        return countSameColorPropertyTiles(player, yelowColorTileIds);
    }
    else if (tile.getId() > 30 and tile.getId() < 35)
    {
        std::vector<uint8_t> greenColorTileIds{31, 32, 34};
        return countSameColorPropertyTiles(player, greenColorTileIds);
    }
    else if (tile.getId() > 35 and tile.getId() < 40)
    {
        std::vector<uint8_t> blueColorTileIds{37, 39};
        return countSameColorPropertyTiles(player, blueColorTileIds);
    }
    return 0;
}

const uint8_t Utils::countSameColorPropertyTiles(const Player &player, const std::vector<uint8_t> sameColorTiles) const
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
