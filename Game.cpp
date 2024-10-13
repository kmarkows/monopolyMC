#include "Game.hpp"

#include "GetOutOfPrisonHandler.hpp"
#include "Logger.hpp"
#include "PlayerRemover.hpp"

Game::Game(const uint32_t givenIterations, const uint8_t givenNumOfPlayers, const DiceThrower *givenDiceThrower,
           const DiceThrowerSingle *givenDiceThrowerSingle)
{
    iterations = givenIterations;
    numOfPlayers = givenNumOfPlayers;
    diceThrower = givenDiceThrower;
    diceThrowerSingle = givenDiceThrowerSingle;
    createPlayersData();
}

void Game::play()
{
    for (uint32_t it = 0; it < iterations; it++)
    {
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logStartOfEachIteration(players, it);
        for (auto &player : players)
        {
            // TO DO write to testGame some tests including houses building
            housesBuilder.tryBuilding(player, board, utils);
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

            const auto &tile = board.getTiles().at(player.getCurrTileId());
            if (cardsEnabled and (utils.isCommunityChestTile(tile) or utils.isChanceTile(tile)))
            {
                handleChanceOrCommunityChestTile(player);
            }

            if (not player.hasInterActedWithTile())
            {
                if (utils.isLuxuryTax(tile) or utils.isIncomeTax(tile))
                {
                    handleTaxTiles(player);
                }

                if (tile.getOwnerId() == invalidPlayerId and buyingEnabled)
                {
                    handleBuyTile(player);
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
                playerRemover.remove(players, player, board);

                if (players.size() == 1)
                {
                    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                                  "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
                    logger.logGameEnd(players);
                    return;
                }
            }
            collectTilesData(player.getCurrTileId());
        }
    }
}

void Game::handleTaxTiles(Player &player)
{
    const auto &tile = board.getTiles().at(player.getCurrTileId());
    const int tax = utils.isIncomeTax(tile) ? 200 : 100;
    player.subtractBalance(tax);
}

void Game::handleBuyTile(Player &player)
{
    // TO DO extract to new class BuyPropertyHandler
    const auto &tile = board.getTiles().at(player.getCurrTileId());
    if (tile.getType() == "Railroad")
    {
        handleBuyTile(player, tile);
        return;
    }

    if (tile.getType() == "Utilities")
    {
        handleBuyTile(player, tile);
        return;
    }

    if (tile.getType() == "Property")
    {
        handleBuyTile(player, tile);
        return;
    }
}

void Game::handleBuyTile(Player &player, const Tile &tile)
{
    // always buy strategy TO DO change that
    const int tileCost = tile.getCost();
    if (player.getCurrentBalance() > tileCost)
    {
        board.getTilesForModification().at(player.getCurrTileId()).setOwnerId(player.getId());
        player.addOwnedTileId(tile.getId());
        player.subtractBalance(tileCost);
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logTileBuying(player, tile);
    }
}

void Game::handleMovement(Player &player)
{
    uint8_t throwCounter = 0;
    bool isDouble = true;
    auto nextTile = player.getCurrTileId();

    while (throwCounter < 3 and isDouble)
    {
        auto diceResult = diceThrower->throwDice();
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
}

void Game::handleChanceOrCommunityChestTile(Player &player)
{
    // staring from beginning TO DO chose first card randomly
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

void Game::createPlayersData()
{
    for (uint8_t id = 1; id < numOfPlayers + 1; id++)
    {
        Player player(id);
        players.push_back(player);
    }
}

void Game::collectTilesData(const uint8_t currTile)
{
    tilesVisitedCounters[currTile]++;
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

const bool Game::isBuyingEnabled() const
{
    return buyingEnabled;
}

void Game::enableBuying()
{
    buyingEnabled = true;
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
