#pragma once

#include "Board.hpp"
#include "DiceThrower.hpp"
#include "DiceThrowerSingle.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include "Chance.hpp"
#include "CommunityChest.hpp"
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

  private:
    void createPlayersData();
    void handleMovement(Player &player);
    void handleTile(Player &player);
    void handleBuyProperty(Player &player, const std::string &currTileType);
    void setPrison(Player &player);
    void handleChanceOrCommunityChestTile(Player& player);

    void collectTilesData(const uint8_t currTile);

    uint32_t iterations;
    uint8_t numOfPlayers;
    std::vector<Player> players{};
    Utils utils;
    const DiceThrower *diceThrower;
    const DiceThrowerSingle *diceThrowerSingle;
    Board board{};
    bool buyingEnabled{false};
    bool cardsEnabled{false};
    CommunityChest communityChest;
    Chance chance;

    std::map<uint8_t, uint32_t> tilesVisitedCounters{};
};
