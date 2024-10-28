#pragma once

#include "BuyingHousesStrategy.hpp"
#include "BuyingTilesStrategy.hpp"
#include "DiceResult.hpp"
#include "Tile.hpp"
#include "TradingStrategy.hpp"

#include <cinttypes>

constexpr uint8_t invalidPlayerId = 0;
constexpr int startingBalance = 1500;

class Player
{
  public:
    Player(uint8_t givenId) : id{givenId} {};

    const bool isInPrison() const;
    const bool hasGetOutOfPrisonCard() const;
    const bool hasGetOutOfPrisonChanceCard() const;
    const bool hasGetOutOfPrisonCommunityChestCard() const;
    const uint8_t getStayingInPrisonStrategy() const;
    const BuyingHousesStrategy getBuyingHousesStrategy() const;
    const BuyingTilesStrategy getBuyingTilesStrategy() const;
    const TradingStrategy getTradingStrategy() const;
    const uint8_t getCurrTileId() const;
    const uint8_t getId() const;
    const uint8_t getTurnsSpentInPrison() const;
    const int getCurrentBalance() const;
    const bool isPlaying() const;
    const bool hasInterActedWithTile() const;
    const std::vector<uint8_t> &getOwnedTilesIds() const;
    const uint8_t getPreviousDiceRollSum() const;

    void goToPrison();
    void acquireGetOutOfPrisonChanceCard();
    void acquireGetOutOfPrisonCommunityChestCard();
    void useGetOutOfPrisonCard();
    void useGetOutOfPrisonChanceCard();
    void useGetOutOfPrisonCommunityChestCard();
    void getOutOfPrison();
    void setStayingInPrisonStrategy(const uint8_t givenStayingInPrisonStrategy);
    void setBuyingHousesStrategy(const BuyingHousesStrategy givenBuyingHousesStrategy);
    void setBuyingTilesStrategy(const BuyingTilesStrategy givenBuyingTilesStrategy);
    void setTradingStrategy(const TradingStrategy givenTradingStrategy);
    void setCurrTile(const uint8_t nextTile);
    void incrementTurnsSpentInPrison();
    void resetTurnsSpentInPrison();
    void setBalance(const int balance);
    void addBalance(const int addition);
    void subtractBalance(const int subtraction);
    void setNotPlaying();
    void setInteractedWithTile();
    void resetInteractedWithTile();
    void addOwnedTileId(const uint8_t newTileId);
    void removeOwnedTileId(const uint8_t newTileId);
    void setPreviousDiceRollSum(const uint8_t previousRoll);

    void print();

  private:
    uint8_t id{invalidPlayerId};
    uint8_t currTile{0};
    bool prison{false};
    bool getOutOfPrisonChanceCard{false};
    bool getOutOfPrisonCommunityChestCard{false};
    bool playing{true};
    uint8_t turnsSpentInPrison{0};
    int balance{startingBalance};
    bool interactedWithTile{false};
    std::vector<uint8_t> ownedTilesIds{};
    uint8_t previousDiceRollSum{0};

    uint8_t stayingInPrisonStrategy{0}; // 0 - 1 - 2, as short - if has Cards uses it - as long
    BuyingHousesStrategy buyingHousesStrategy{};
    BuyingTilesStrategy buyingTilesStrategy{};
    TradingStrategy tradingStrategy{};
};