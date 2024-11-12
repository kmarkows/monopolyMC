#include "Logger.hpp"

Logger::Logger()
{
    logFile.open(fileName, std::ios::app);
    if (!logFile.is_open())
    {
        std::cout << "Error: Could not open the monopolyGameLogs.txt file!" << std::endl;
    }
}

Logger::~Logger()
{
    logFile.close();
}

void Logger::logStartOfEachIteration(const std::vector<Player> &players, const Board &board, const uint32_t iteration)
{
    logFile << "---------------------------------- Start of iteration:" << (int)iteration
            << " ----------------------------------" << std::endl;
    for (const auto &player : players)
    {
        logFile << "PlayerId:" << (int)player.getId() << " currTileId:" << (int)player.getCurrTileId()
                << " currBalance:" << player.getCurrentBalance() << " isInPrison:" << player.isInPrison()
                << " hasGetOutOfPrisonCard:" << player.hasGetOutOfPrisonCard() << " ownedTiles:[";
        for (uint8_t i = 0; i < player.getOwnedTilesIds().size(); i++)
        {
            logFile << (int)player.getOwnedTilesIds()[i] << "("
                    << (int)board.getTiles().at(player.getOwnedTilesIds()[i]).getNumOfHouses() << ")";
            if (i != player.getOwnedTilesIds().size() - 1)
            {
                logFile << ", ";
            }
        }
        logFile << "]" << std::endl;
    }
    logFile << std::endl;
}

void Logger::logDiceRolling(const Player &player, const DiceResult &diceResult)
{
    logFile << "PlayerId:" << (int)player.getId() << " rolls:[" << (int)diceResult.getFirst() << ", "
            << (int)diceResult.getSecond() << "]" << std::endl;
}

void Logger::logMovement(const Player &player)
{
    logFile << "PlayerId:" << (int)player.getId() << " endsOnTile:" << (int)player.getCurrTileId() << std::endl;
}

void Logger::logTryTileBuying(const Player &player, const Tile &tile)
{
    logFile << "PlayerId:" << (int)player.getId() << " currBalance:" << player.getCurrentBalance()
            << " firstHalfPropertiesFactor:" << player.getBuyingTilesStrategy().firstHalfPropertiesFactor
            << " secondHalfPropertiesFactor:" << player.getBuyingTilesStrategy().secondHalfPropertiesFactor
            << " moneyToSpentAtTilesBuying:" << player.getBuyingTilesStrategy().moneyToSpentAtTilesBuying
            << " triesToBuyTileId:" << (int)player.getCurrTileId() << " tileCost:" << tile.getCost() << std::endl;
}

void Logger::logTileBuying(const Player &player, const Tile &tile)
{
    logFile << "PlayerId:" << (int)player.getId() << " boughtTileNumer:" << (int)tile.getId()
            << " for:" << tile.getCost() << " balanceLeft:" << player.getCurrentBalance() << std::endl;
}

void Logger::logTryHouseBuying(const Player &player, const int8_t availableHouses, const int8_t availablHotels)
{
    logFile << "PlayerId:" << (int)player.getId() << " triesToBuyHouses"
            << " currBalance:" << player.getCurrentBalance()
            << " moneyToSpentAtHouseBuying:" << player.getBuyingHousesStrategy().moneyToSpentAtHouseBuying
            << " colorPriority:" << (int)player.getBuyingHousesStrategy().colorPriority
            << " availableHouses:" << (int)availableHouses << " availableHotels:" << (int)availablHotels << std::endl;
}

void Logger::logHouseBuying(const Player &player, const Tile &tile, const int8_t availableHouses,
                            const int8_t availablHotels)
{
    logFile << "PlayerId:" << (int)player.getId() << " boughtHouseNumber:" << (int)tile.getNumOfHouses()
            << " onTile:" << (int)tile.getId() << " for:" << tile.getHouseCost()
            << " balanceLeft:" << player.getCurrentBalance() << " availableHouses:" << (int)availableHouses
            << " availableHotels:" << (int)availablHotels << std::endl;
}

void Logger::logTryTilesTrading(const Player &player)
{
    logFile << "PlayerId:" << (int)player.getId() << " currBalance:" << player.getCurrentBalance() << " ownedTiles:[";
    for (uint8_t i = 0; i < player.getOwnedTilesIds().size(); i++)
    {
        logFile << (int)player.getOwnedTilesIds()[i];
        if (i != player.getOwnedTilesIds().size() - 1)
        {
            logFile << ", ";
        }
    }
    logFile << "] triesTilesTrading" << std::endl;
}

void Logger::logTilesTrading(const Player &player, const Player &owner, const Tile &tile, const int price)
{
    logFile << "PlayerId:" << (int)player.getId() << " buughtTileId:" << (int)tile.getId()
            << " fromOwner:" << (int)owner.getId() << " for:" << price << " currBalance:" << player.getCurrentBalance()
            << " ownedTiles:[";
    for (uint8_t i = 0; i < player.getOwnedTilesIds().size(); i++)
    {
        logFile << (int)player.getOwnedTilesIds()[i];
        if (i != player.getOwnedTilesIds().size() - 1)
        {
            logFile << ", ";
        }
    }
    logFile << "]" << std::endl;
}

void Logger::logPlayerGoesToPrison(const Player &player)
{
    logFile << "PlayerId:" << (int)player.getId() << " goToPrison" << std::endl;
}

void Logger::logPlayerTriesToGetOutOfPrison(const Player &player)
{
    logFile << "PlayerId:" << (int)player.getId() << " currBalance:" << player.getCurrentBalance()
            << " triesToGetOutOfPrison strategy:" << (int)player.getStayingInPrisonStrategy()
            << " hasGetOutOfPrisonCard:" << player.hasGetOutOfPrisonCard() << std::endl;
}

void Logger::logPlayerGetsOutOfPrisonByCard(const Player &player, const DiceResult &diceResult)
{
    logFile << "PlayerId:" << (int)player.getId() << " getOutOfPrisonByUsingCard"
            << " hasGetOutOfPrisonCard:" << player.hasGetOutOfPrisonCard() << " first:" << (int)diceResult.getFirst()
            << " second:" << (int)diceResult.getSecond() << std::endl;
}

void Logger::logPlayerGetsOutOfPrisonByFine(const Player &player, const DiceResult &diceResult)
{
    logFile << "PlayerId:" << (int)player.getId() << " getOutOfPrisonByPayingFine"
            << " currBalance:" << player.getCurrentBalance() << " first:" << (int)diceResult.getFirst()
            << " second:" << (int)diceResult.getSecond() << std::endl;
}

void Logger::logPlayerGetsOutOfPrisonByDouble(const Player &player, const DiceResult &diceResult)
{
    logFile << "PlayerId:" << (int)player.getId() << " getOutOfPrisonByThrowingDouble"
            << " first:" << (int)diceResult.getFirst() << " second:" << (int)diceResult.getSecond() << std::endl;
}

void Logger::logPlayerGetsOutOfPrisonByStaying(const Player &player, const DiceResult &diceResult)
{
    logFile << "PlayerId:" << (int)player.getId() << " getOutOfPrisonByStayingThreeTurns"
            << " currBalance:" << player.getCurrentBalance() << " first:" << (int)diceResult.getFirst()
            << " second:" << (int)diceResult.getSecond() << std::endl;
}

void Logger::logDrawCardCommunityChest(const Player &player, const uint8_t cardToBeDrawed)
{
    logFile << "PlayerId:" << (int)player.getId() << " drawsCommunityChestCardId:" << (int)cardToBeDrawed << std::endl;
}

void Logger::logDrawCardChance(const Player &player, const uint8_t cardToBeDrawed)
{
    logFile << "PlayerId:" << (int)player.getId() << " drawsChanceCardId:" << (int)cardToBeDrawed << std::endl;
}

void Logger::logRentPayer(const Player &player, const Player &owner, const Tile &tile)
{
    logFile << "PlayerId:" << (int)player.getId() << " currBalance:" << player.getCurrentBalance()
            << " goesOnTileId:" << (int)tile.getId() << " tileType:" << tile.getType()
            << " numOfHouses:" << (int)tile.getNumOfHouses() << " hasToPayRentToOwnerId:" << (int)owner.getId()
            << " currBalance:" << owner.getCurrentBalance() << std::endl;
}

void Logger::logPayingRent(const Player &player, const Player &owner, const int rent)
{
    logFile << "PlayerId:" << (int)player.getId() << " currBalance:" << player.getCurrentBalance()
            << " paidRent:" << rent << " hasToPayRentToOwnerId:" << (int)owner.getId()
            << " currBalance:" << owner.getCurrentBalance() << std::endl;
}

void Logger::logRemovePlayer(const Player &player, const Board &board)
{
    logFile << "PlayerId:" << (int)player.getId() << " currBalance:" << player.getCurrentBalance() << " ownedTiles:[";

    for (uint8_t i = 0; i < player.getOwnedTilesIds().size(); i++)
    {
        logFile << (int)player.getOwnedTilesIds()[i] << "("
                << (int)board.getTiles().at(player.getOwnedTilesIds()[i]).getNumOfHouses() << ")";
        if (i != player.getOwnedTilesIds().size() - 1)
        {
            logFile << ", ";
        }
    }
    logFile << "]" << " isRemovedFromTheGame" << std::endl;
}

void Logger::logGameEnd(const std::vector<Player> &players)
{
    logFile << "PlayerId:" << (int)players[0].getId() << " currBalance:" << players[0].getCurrentBalance()
            << " ownedTiles:[";
    for (uint8_t i = 0; i < players[0].getOwnedTilesIds().size(); i++)
    {
        logFile << (int)players[0].getOwnedTilesIds()[i];
        if (i != players[0].getOwnedTilesIds().size() - 1)
        {
            logFile << ", ";
        }
    }
    logFile << "]" << " winsTheGame" << std::endl;
}

void Logger::playerEndsTurn()
{
    logFile << std::endl;
}
