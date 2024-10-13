#include "TileBuyer.hpp"

#include "Logger.hpp"

void TileBuyer::tryBuying(Player &player, Board &board, const Utils &utils)
{
    auto &tile = board.getTilesForModification().at(player.getCurrTileId());
    if (tile.getType() == "Railroad" or tile.getType() == "Utilities" or tile.getType() == "Property")
    {
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logTryTileBuying(player, tile);
        handleBuyableTile(player, tile, utils);
    }
}

void TileBuyer::handleBuyableTile(Player &player, Tile &tile, const Utils &utils)
{
    const uint8_t numberOfSimilarColorTiles = utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile);
    const int tileCost = tile.getId() < 20
                             ? tile.getCost() * player.getBuyingTilesStrategy().firstHalfPropertiesFactor
                             : tile.getCost() * player.getBuyingTilesStrategy().secondHalfPropertiesFactor;
    const int moneyToSpentOnTileBuying =
        player.getCurrentBalance() * player.getBuyingTilesStrategy().moneyToSpentAtTilesBuying;

    if (numberOfSimilarColorTiles > 0 and player.getCurrentBalance() > tile.getCost())
    {
        buyTile(player, tile);
    }
    else if (moneyToSpentOnTileBuying > tileCost)
    {
        buyTile(player, tile);
    }
}

void TileBuyer::buyTile(Player &player, Tile &tile)
{
    tile.setOwnerId(player.getId());
    player.addOwnedTileId(tile.getId());
    player.subtractBalance(tile.getCost());
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logTileBuying(player, tile);
}