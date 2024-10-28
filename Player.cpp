#include "Player.hpp"

#include "Logger.hpp"

#include <iostream>

void Player::print()
{
    std::cout << "player id:" << (int)id << " currentTile:" << (int)currTile << std::endl;
}

const bool Player::isInPrison() const
{
    return prison;
}

const bool Player::hasGetOutOfPrisonCard() const
{
    return getOutOfPrisonChanceCard or getOutOfPrisonCommunityChestCard;
}

const bool Player::hasGetOutOfPrisonChanceCard() const
{
    return getOutOfPrisonChanceCard;
}

const bool Player::hasGetOutOfPrisonCommunityChestCard() const
{
    return getOutOfPrisonCommunityChestCard;
}

const uint8_t Player::getStayingInPrisonStrategy() const
{
    return stayingInPrisonStrategy;
}

const BuyingHousesStrategy Player::getBuyingHousesStrategy() const
{
    return buyingHousesStrategy;
}

const BuyingTilesStrategy Player::getBuyingTilesStrategy() const
{
    return buyingTilesStrategy;
}

const TradingStrategy Player::getTradingStrategy() const
{
    return tradingStrategy;
}

const uint8_t Player::getCurrTileId() const
{
    return currTile;
}

const uint8_t Player::getId() const
{
    return id;
}

const uint8_t Player::getTurnsSpentInPrison() const
{
    return turnsSpentInPrison;
}

const int Player::getCurrentBalance() const
{
    return balance;
}

const bool Player::isPlaying() const
{
    return playing;
}

const bool Player::hasInterActedWithTile() const
{
    return interactedWithTile;
}

const std::vector<uint8_t> &Player::getOwnedTilesIds() const
{
    return ownedTilesIds;
}

const uint8_t Player::getPreviousDiceRollSum() const
{
    return previousDiceRollSum;
}

void Player::goToPrison()
{
    // TO DO log going to prison different ways
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logPlayerGoesToPrison(*this);
    prison = true;
}

void Player::acquireGetOutOfPrisonChanceCard()
{
    getOutOfPrisonChanceCard = true;
}

void Player::acquireGetOutOfPrisonCommunityChestCard()
{
    getOutOfPrisonCommunityChestCard = true;
}

void Player::useGetOutOfPrisonCard()
{
    if (hasGetOutOfPrisonCard())
    {
        hasGetOutOfPrisonChanceCard() ? useGetOutOfPrisonChanceCard() : useGetOutOfPrisonCommunityChestCard();
    }
}

void Player::useGetOutOfPrisonChanceCard()
{
    getOutOfPrisonChanceCard = false;
}

void Player::useGetOutOfPrisonCommunityChestCard()
{
    getOutOfPrisonCommunityChestCard = false;
}

void Player::getOutOfPrison()
{
    prison = false;
}

void Player::setStayingInPrisonStrategy(const uint8_t givenStayingInPrisonStrategy)
{
    stayingInPrisonStrategy = givenStayingInPrisonStrategy;
}

void Player::setBuyingHousesStrategy(const BuyingHousesStrategy givenBuyingHousesStrategy)
{
    buyingHousesStrategy = givenBuyingHousesStrategy;
}

void Player::setBuyingTilesStrategy(const BuyingTilesStrategy givenBuyingTilesStrategy)
{
    buyingTilesStrategy = givenBuyingTilesStrategy;
}

void Player::setTradingStrategy(const TradingStrategy givenTradingStrategy)
{
    tradingStrategy = givenTradingStrategy;
}

void Player::setCurrTile(const uint8_t nextTile)
{
    currTile = nextTile;
}

void Player::incrementTurnsSpentInPrison()
{
    turnsSpentInPrison++;
}

void Player::resetTurnsSpentInPrison()
{
    turnsSpentInPrison = 0;
}

void Player::setBalance(const int balance)
{
    this->balance = balance;
}

void Player::addBalance(const int addition)
{
    balance += addition;
}

void Player::subtractBalance(const int subtraction)
{
    balance -= subtraction;
    if (balance <= 0)
    {
        setNotPlaying();
    }
}

void Player::setNotPlaying()
{
    playing = false;
}

void Player::setInteractedWithTile()
{
    interactedWithTile = true;
}

void Player::resetInteractedWithTile()
{
    interactedWithTile = false;
}

void Player::addOwnedTileId(const uint8_t newTileId)
{
    ownedTilesIds.push_back(newTileId);
    std::sort(ownedTilesIds.begin(), ownedTilesIds.end());
}

void Player::removeOwnedTileId(const uint8_t tileIdToRemove)
{
    auto it = std::find(ownedTilesIds.begin(), ownedTilesIds.end(), tileIdToRemove);
    ownedTilesIds.erase(it);
    std::sort(ownedTilesIds.begin(), ownedTilesIds.end());
}

void Player::setPreviousDiceRollSum(const uint8_t previousRoll)
{
    previousDiceRollSum = previousRoll;
}
