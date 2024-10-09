#pragma once

#include "Board.hpp"
#include "Chance.hpp"
#include "CommunityChest.hpp"
#include "DiceThrower.hpp"
#include "DiceThrowerSingle.hpp"
#include "HousesBuilder.hpp"
#include "Player.hpp"
#include "RentPayer.hpp"
#include "Utils.hpp"
#include <map>
#include <optional>
#include <vector>

class Game
{
  public:
    Game() = default;
    Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower,
         const DiceThrowerSingle *givenDiceThrowerSingle);
    void play();

    void printPlayersData();
    void printTilesVisitedCounters();
    void printPropertiesData();

    std::vector<Player> &getPlayersDataForManipulation();
    const std::vector<Player> &getPlayersData() const;
    Player &getPlayerByIdForManipulation(const uint8_t playerId);
    const Player &getPlayerById(const uint8_t playerId) const;

    const Board &getBoardData() const;
    Board &getBoardDataForModification();

    const Utils &getUtils() const;

    const bool isBuyingEnabled() const;
    void enableBuying();

    const bool areCardsEnabled() const;
    void enableCards();

    const bool isPayingEnabled() const;
    void enablePaying();

  private:
    void createPlayersData();
    void handleMovement(Player &player);
    void handleTaxTiles(Player &player);
    void handleBuyTile(Player &player);
    void handleBuyTile(Player &player, const Tile &tile);
    void setPrison(Player &player);
    void handleChanceOrCommunityChestTile(Player &player);

    void collectTilesData(const uint8_t currTile);

    uint32_t iterations;
    uint8_t numOfPlayers;
    std::vector<Player> players{};
    const DiceThrower *diceThrower;
    const DiceThrowerSingle *diceThrowerSingle;
    Board board{};
    bool buyingEnabled{false};
    bool cardsEnabled{false};
    bool payingEnabled{false};
    Utils utils;
    RentPayer rentPayer;
    HousesBuilder housesBuilder;
    CommunityChest communityChest;
    Chance chance;

    std::map<uint8_t, uint32_t> tilesVisitedCounters{};
};
