#pragma once

#include "Board.hpp"
#include "Chance.hpp"
#include "CommunityChest.hpp"
#include "DiceThrower.hpp"
#include "HousesBuilder.hpp"
#include "Player.hpp"
#include "RentPayer.hpp"
#include "TileBuyer.hpp"
#include "Trader.hpp"
#include "Utils.hpp"

#include <map>
#include <optional>
#include <vector>

class Game
{
  public:
    Game() = default;
    Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower,
         const std::vector<uint8_t> &playersOrder);
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

    CommunityChest &getCommunityChestForModification();
    Chance &getChanceForModification();

    const bool isTradingTilesEnabled() const;
    void enableTilesTrading();

    const bool isBuyingTilesEnabled() const;
    void enableTilesBuying();

    const bool isBuyingHousesEnabled() const;
    void enableHousesBuying();

    const bool areCardsEnabled() const;
    void enableCards();

    const bool isPayingEnabled() const;
    void enablePaying();

  private:
    void createPlayersData(const std::vector<uint8_t> &playersOrder);
    void handleMovement(Player &player);
    void handleTaxTiles(Player &player);
    void setPrison(Player &player);
    void handleChanceOrCommunityChestTile(Player &player);

    void collectTilesData(const uint8_t currTile);
    void saveTilesData();
    void saveWinningPlayerData(const uint8_t playerId);

    uint32_t iterations;
    uint8_t numOfPlayers;
    std::vector<Player> players{};
    const DiceThrower *diceThrower;
    Board board{};
    bool tradingEnabled{false};
    bool tilesBuyingEnabled{false};
    bool housesBuyingEnabled{false};
    bool cardsEnabled{false};
    bool payingEnabled{false};
    Utils utils;
    RentPayer rentPayer;
    TileBuyer tileBuyer;
    Trader trader;
    HousesBuilder housesBuilder;
    CommunityChest communityChest;
    Chance chance;

    std::map<uint8_t, uint32_t> tilesVisitedCounters{};
};
