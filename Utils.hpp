#pragma once

#include <vector>

#include "Board.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Utils
{
  public:
    Utils() = default;
    const uint8_t getNumOfTilesOfEachTypeOwnedByPlayer(const Player &player, const Tile &tile) const;
    const std::vector<std::vector<uint8_t>> getTileIdsOnWhichPlayerCanBuildHouses(const Player &player,
                                                                                  const Board &board) const;
    const uint8_t getMaxNumOfHousesThatCanBeBuildOnGivenTile(const Tile &tile, const Board &board) const;
    const bool isChanceTile(const Tile &tile) const;
    const bool isCommunityChestTile(const Tile &tile) const;
    const bool isIncomeTax(const Tile &tile) const;
    const bool isLuxuryTax(const Tile &tile) const;

  private:
    const uint8_t countRailroadTiles(const Player &player) const;
    const uint8_t countUtilityTiles(const Player &player) const;
    const uint8_t countPropertyTiles(const Player &player, const Tile &tile) const;
    const uint8_t countSameColorPropertyTiles(const Player &player, const std::vector<uint8_t> &sameColorTiles) const;
    void checkIfBuildingPossibleOnGivenColorTiles(
        const Player &player, const std::vector<uint8_t> &sameColorTiles,
        std::vector<std::vector<uint8_t>> &tileIdsOnWhichPlayerCanBuild) const;
    const uint8_t getMinNumberOfHousesOnSameColorTiles(const Board &board,
                                                       const std::vector<uint8_t> &sameColorTiles) const;

    std::vector<uint8_t> brownColorTileIds{1, 3};
    std::vector<uint8_t> lightBlueColorTileIds{6, 8, 9};
    std::vector<uint8_t> pinkColorTileIds{11, 13, 14};
    std::vector<uint8_t> orangeColorTileIds{16, 18, 19};
    std::vector<uint8_t> redColorTileIds{21, 23, 24};
    std::vector<uint8_t> yelowColorTileIds{26, 27, 29};
    std::vector<uint8_t> greenColorTileIds{31, 32, 34};
    std::vector<uint8_t> blueColorTileIds{37, 39};
};
