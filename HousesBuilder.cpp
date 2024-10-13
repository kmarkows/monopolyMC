#include "HousesBuilder.hpp"
#include "Logger.hpp"

// TO DO refactoring
// TO DO divide into houses and hotels building

void HousesBuilder::tryBuilding(Player &player, Board &board, const Utils &utils)
{
    moneyToSpentAtHouseBuying = player.getBuyingHousesStrategy().moneyToSpentAtHouseBuying * player.getCurrentBalance();
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                  "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logTryHouseBuying(player, availableHouses, availablHotels);
    if (player.getBuyingHousesStrategy().colorPriority == 0)
    {
        const auto &tileIdsOnWhichPlayerCanBuildHouses = utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board);
        for (int8_t i = 0; i < tileIdsOnWhichPlayerCanBuildHouses.size(); i++)
        {
            const auto &sameColorTileIdsOnWhichPlayerCanBuild = tileIdsOnWhichPlayerCanBuildHouses[i];
            const Tile &firstTileOfGivenColor = board.getTiles().at(sameColorTileIdsOnWhichPlayerCanBuild[0]);
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) < 5 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost())
            {
                for (int8_t j = 0; j < sameColorTileIdsOnWhichPlayerCanBuild.size(); j++)
                {
                    auto &tileOnPlayerTriesToBuild =
                        board.getTilesForModification().at(sameColorTileIdsOnWhichPlayerCanBuild[j]);
                    buildHouses(player, tileOnPlayerTriesToBuild, board, utils);
                }
            }
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) == 5 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost() and
                   player.getBuyingHousesStrategy().isBuyingHotels)
            {
                for (int8_t j = 0; j < sameColorTileIdsOnWhichPlayerCanBuild.size(); j++)
                {
                    auto &tileOnPlayerTriesToBuild =
                        board.getTilesForModification().at(sameColorTileIdsOnWhichPlayerCanBuild[j]);
                    buildHotels(player, tileOnPlayerTriesToBuild, board, utils);
                }
            }
        }
    }
    else if (player.getBuyingHousesStrategy().colorPriority == 1)
    {
        const auto &tileIdsOnWhichPlayerCanBuildHouses = utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board);
        for (int8_t i = tileIdsOnWhichPlayerCanBuildHouses.size() - 1; i >= 0; i--)
        {
            const auto &sameColorTileIdsOnWhichPlayerCanBuild = tileIdsOnWhichPlayerCanBuildHouses[i];
            const Tile &firstTileOfGivenColor = board.getTiles().at(sameColorTileIdsOnWhichPlayerCanBuild[0]);
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) < 5 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost())
            {
                for (int8_t j = sameColorTileIdsOnWhichPlayerCanBuild.size() - 1; j >= 0; j--)
                {
                    auto &tileOnPlayerTriesToBuild =
                        board.getTilesForModification().at(sameColorTileIdsOnWhichPlayerCanBuild[j]);
                    buildHouses(player, tileOnPlayerTriesToBuild, board, utils);
                }
            }
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) == 5 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost() and
                   player.getBuyingHousesStrategy().isBuyingHotels)
            {
                for (int8_t j = sameColorTileIdsOnWhichPlayerCanBuild.size() - 1; j >= 0; j--)
                {
                    auto &tileOnPlayerTriesToBuild =
                        board.getTilesForModification().at(sameColorTileIdsOnWhichPlayerCanBuild[j]);
                    buildHotels(player, tileOnPlayerTriesToBuild, board, utils);
                }
            }
        }
    }
}

void HousesBuilder::buildHouses(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils)
{

    if (tileOnPlayerTriesToBuild.getNumOfHouses() <
            utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tileOnPlayerTriesToBuild, board) and
        moneyToSpentAtHouseBuying >= tileOnPlayerTriesToBuild.getHouseCost() and availableHouses > 0)
    {
        tileOnPlayerTriesToBuild.buildHouse();
        player.subtractBalance(tileOnPlayerTriesToBuild.getHouseCost());
        moneyToSpentAtHouseBuying -= tileOnPlayerTriesToBuild.getHouseCost();
        availableHouses--;
        Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                      "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logHouseBuying(player, tileOnPlayerTriesToBuild);
    }
}

void HousesBuilder::buildHotels(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils)
{

    if (tileOnPlayerTriesToBuild.getNumOfHouses() <
            utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tileOnPlayerTriesToBuild, board) and
        moneyToSpentAtHouseBuying >= tileOnPlayerTriesToBuild.getHouseCost() and availablHotels > 0)
    {
        tileOnPlayerTriesToBuild.buildHouse();
        player.subtractBalance(tileOnPlayerTriesToBuild.getHouseCost());
        moneyToSpentAtHouseBuying -= tileOnPlayerTriesToBuild.getHouseCost();
        availablHotels--;
        Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                      "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logHouseBuying(player, tileOnPlayerTriesToBuild);
    }
}
