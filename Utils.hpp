#pragma once

#include <vector>

#include "Board.hpp"
#include "Player.hpp"
#include "Tile.hpp"

constexpr uint8_t totalNumberOfRailroadTiles = 4;
constexpr uint8_t totalNumberOfUtilityTiles = 2;

class Utils
{
  public:
    Utils() = default;

    Player &getPlayerByIdForManipulation(std::vector<Player> &players, const uint8_t playerId) const;
    const Player &getPlayerById(const std::vector<Player> &players, const uint8_t playerId) const;

    const int8_t getNumOfTilesOfGivenTypeMissingByPlayer(const Player &player, const Tile &tile) const;
    const std::vector<uint8_t> getTileIdsOfGivenTypeMissingByPlayer(const Player &player, const Tile &tile) const;
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
    const int8_t countMissingPropertyTiles(const Player &player, const Tile &tile) const;
    const uint8_t countSameColorPropertyTiles(const Player &player, const std::vector<uint8_t> &sameColorTiles) const;
    void checkIfBuildingPossibleOnGivenColorTiles(
        const Player &player, const std::vector<uint8_t> &sameColorTiles,
        std::vector<std::vector<uint8_t>> &tileIdsOnWhichPlayerCanBuild) const;
    const uint8_t getMinNumberOfHousesOnSameColorTiles(const Board &board,
                                                       const std::vector<uint8_t> &sameColorTiles) const;
    void getTileIdsOfRailroadsMissingByPlayer(const Player &player, std::vector<uint8_t> &tileIdsMissingByPlayer) const;
    void getTileIdsOfUtilitiesMissingByPlayer(const Player &player, std::vector<uint8_t> &tileIdsMissingByPlayer) const;
    void getTileIdsOfPropertiesMissingByPlayer(const Player &player, const Tile &tile,
                                               std::vector<uint8_t> &tileIdsMissingByPlayer) const;
    void getTileIdsOfPropertiesMissingByPlayerOfEachColor(const Player &player,
                                                          const std::vector<uint8_t> &brownColorTileIds,
                                                          std::vector<uint8_t> &tileIdsMissingByPlayer) const;

    std::vector<uint8_t> brownColorTileIds{1, 3};
    std::vector<uint8_t> lightBlueColorTileIds{6, 8, 9};
    std::vector<uint8_t> pinkColorTileIds{11, 13, 14};
    std::vector<uint8_t> orangeColorTileIds{16, 18, 19};
    std::vector<uint8_t> redColorTileIds{21, 23, 24};
    std::vector<uint8_t> yelowColorTileIds{26, 27, 29};
    std::vector<uint8_t> greenColorTileIds{31, 32, 34};
    std::vector<uint8_t> blueColorTileIds{37, 39};
    std::vector<uint8_t> railroadTileIds{5, 15, 25, 35};
    std::vector<uint8_t> utilitiesTileIds{12, 28};
};
