#include "Game.hpp"

#include "GetOutOfPrisonHandler.hpp"
#include "Logger.hpp"
#include "PlayerRemover.hpp"

Game::Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower,
           const std::vector<uint8_t> &playersOrder)
{
    iterations = givenIterations;
    numOfPlayers = givenNumOfPlayers;
    diceThrower = givenDiceThrower;
    createPlayersData(playersOrder);
    chance.setNextCardIdToBePlayed((rand() % chanceCardsNumber));
    communityChest.setNextCardIdToBePlayed((rand() % communityChestCardsNumber));
}

void Game::play()
{
    for (uint32_t it = 0; it < iterations; it++)
    {
        Logger logger;
        logger.logStartOfEachIteration(players, board, it);
        for (uint8_t i = 0; i < players.size(); i++)
        {
            auto &player = players.at(i);
            player.resetInteractedWithTile();

            if (tradingEnabled and player.getOwnedTilesIds().size() != 0)
            {
                trader.trade(player, players, board, utils);
            }

            if (housesBuyingEnabled and player.getOwnedTilesIds().size() != 0)
            {
                housesBuilder.tryBuilding(player, board, utils);
            }

            if (not player.isInPrison())
            {
                handleMovement(player);
                if (player.getCurrTileId() == goToPrisonTile)
                {
                    setPrison(player);
                }
            }
            else
            {
                GetOutOfPrisonHandler getOutOfPrisonHandler(player, diceThrower);
                getOutOfPrisonHandler.handle();
            }

            if (cardsEnabled and (utils.isCommunityChestTile(board.getTiles().at(player.getCurrTileId())) or
                                  utils.isChanceTile(board.getTiles().at(player.getCurrTileId()))))
            {
                handleChanceOrCommunityChestTile(player);
            }

            const auto &tile = board.getTiles().at(player.getCurrTileId());
            if (not player.hasInterActedWithTile())
            {
                if (utils.isLuxuryTax(tile) or utils.isIncomeTax(tile))
                {
                    handleTaxTiles(player);
                }

                if (tile.getOwnerId() == invalidPlayerId and tilesBuyingEnabled)
                {
                    tileBuyer.tryBuying(player, board, utils);
                }
                else if (tile.getOwnerId() != player.getId() and payingEnabled)
                {
                    rentPayer.payRent(player, getPlayerByIdForManipulation(tile.getOwnerId()), tile,
                                      player.getPreviousDiceRollSum());
                }
            }

            if (not player.isPlaying())
            {
                PlayerRemover playerRemover;
                playerRemover.remove(players, player, board, communityChest, chance, housesBuilder);

                if (players.size() == 1)
                {
                    Logger logger;
                    logger.logGameEnd(players);
                    saveWinningPlayerData(players[0].getId());
                    saveTilesData();
                    return;
                }
                i--;
            }
            collectTilesData(player.getCurrTileId());
            Logger logger;
            logger.playerEndsTurn();
        }
    }
}

void Game::handleTaxTiles(Player &player)
{
    const auto &tile = board.getTiles().at(player.getCurrTileId());
    const int tax = utils.isIncomeTax(tile) ? 200 : 100;
    player.subtractBalance(tax);
}

void Game::handleMovement(Player &player)
{
    // TO DO log moving
    uint8_t throwCounter = 0;
    bool isDouble = true;
    auto nextTile = player.getCurrTileId();

    while (throwCounter < 3 and isDouble)
    {
        auto diceResult = diceThrower->throwDice();
        Logger logger;
        logger.logDiceRolling(player, diceResult);
        isDouble = diceResult.getFirst() == diceResult.getSecond();
        throwCounter++;

        nextTile += (diceResult.getFirst() + diceResult.getSecond());
        player.setPreviousDiceRollSum(diceResult.getFirst() + diceResult.getSecond());
    }

    if (throwCounter == 3 and isDouble)
    {
        setPrison(player);
        return;
    }

    if (nextTile / numOfMonopolyBoradTiles == 1)
    {
        player.addBalance(200);
    }

    nextTile = nextTile % numOfMonopolyBoradTiles;
    player.setCurrTile(nextTile);
    Logger logger;
    logger.logMovement(player);
}

void Game::handleChanceOrCommunityChestTile(Player &player)
{
    if (utils.isChanceTile(board.getTiles().at(player.getCurrTileId())))
    {
        chance.playNextCard(*this, player, diceThrower);
    }
    else
    {
        communityChest.playNextCard(*this, player, diceThrower);
    }
}

void Game::setPrison(Player &player)
{
    player.goToPrison();
    player.setCurrTile(prisonTile);
}

void Game::createPlayersData(const std::vector<uint8_t> &playersOrder)
{
    for (uint8_t i = 0; i < playersOrder.size(); i++)
    {
        Player player(playersOrder[i]);
        players.push_back(player);
    }
}

void Game::collectTilesData(const uint8_t currTile)
{
    tilesVisitedCounters[currTile]++;
}

void Game::saveTilesData()
{
    std::ofstream file(
        "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/statistics/tilesVisitsCounter.txt",
        std::ios::app);
    if (!file)
    {
        std::cout << "Error: Could not open the winningPlayers.txt file!" << std::endl;
        return;
    }
    for (const auto &[key, value] : tilesVisitedCounters)
    {
        file << (int)key << "(" << (int)value << ") ";
    }
    file << std::endl;
    file.close();
}

void Game::saveWinningPlayerData(const uint8_t playerId)
{
    std::ofstream file(
        "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/statistics/winningPlayers.txt",
        std::ios::app);
    if (!file)
    {
        std::cout << "Error: Could not open the winningPlayers.txt file!" << std::endl;
        return;
    }
    file << (int)playerId << " ";
    file.close();
}

void Game::printTilesVisitedCounters()
{
    for (const auto &[tile, counter] : tilesVisitedCounters)
    {
        std::cout << "tile:" << (int)tile << " number of visits:" << (int)counter << std::endl;
    }
}

void Game::printPlayersData()
{
    for (uint8_t id = 0; id < numOfPlayers; id++)
    {
        players.at(id).print();
    }
}

void Game::printPropertiesData()
{
    for (const auto &tile : getBoardData().getTiles())
    {
        if (tile.getType() == "Property")
        {
            std::cout << "tile:" << (int)tile.getId() << " owner:" << (int)tile.getOwnerId() << std::endl;
        }
    }
}

std::vector<Player> &Game::getPlayersDataForManipulation()
{
    return players;
}

const std::vector<Player> &Game::getPlayersData() const
{
    return players;
}

const Board &Game::getBoardData() const
{
    return board;
}

Board &Game::getBoardDataForModification()
{
    return board;
}

const Utils &Game::getUtils() const
{
    return utils;
}

CommunityChest &Game::getCommunityChestForModification()
{
    return communityChest;
}

Chance &Game::getChanceForModification()
{
    return chance;
}

const bool Game::isBuyingTilesEnabled() const
{
    return tilesBuyingEnabled;
}

void Game::enableTilesBuying()
{
    tilesBuyingEnabled = true;
}

const bool Game::isTradingTilesEnabled() const
{
    return tradingEnabled;
}

void Game::enableTilesTrading()
{
    tradingEnabled = true;
}

const bool Game::isBuyingHousesEnabled() const
{
    return housesBuyingEnabled;
}

void Game::enableHousesBuying()
{
    housesBuyingEnabled = true;
}

const bool Game::areCardsEnabled() const
{
    return cardsEnabled;
}

void Game::enableCards()
{
    cardsEnabled = true;
}

const bool Game::isPayingEnabled() const
{
    return payingEnabled;
}

void Game::enablePaying()
{
    payingEnabled = true;
}

Player &Game::getPlayerByIdForManipulation(const uint8_t playerId)
{
    // TO DO not finding player functionality
    for (auto &player : players)
    {
        if (player.getId() == playerId)
        {
            return player;
        }
    }
    std::cout << "Player with id:" << (int)playerId << " not found" << std::endl;
    return players.at(0);
}

const Player &Game::getPlayerById(const uint8_t playerId) const
{
    // TO DO not finding player functionality
    for (const auto &player : players)
    {
        if (player.getId() == playerId)
        {
            return player;
        }
    }
    std::cout << "Player with id:" << (int)playerId << " not found" << std::endl;
    return players.at(0);
}
