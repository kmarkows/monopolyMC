#include "HousesBuilder.hpp"
#include "Logger.hpp"

// TO DO refactoring
void HousesBuilder::tryBuilding(Player &player, Board &board, const Utils &utils)
{
    int moneyToSpentAtHouseBuying =
        player.getBuyingHousesStrategy().moneyToSpentAtHouseBuying * player.getCurrentBalance();
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                  "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logTryHouseBuying(player);
    if (player.getBuyingHousesStrategy().colorPriority == 0)
    {
        const auto &tileIdsOnWhichPlayerCanBuildHouses = utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board);
        for (int8_t i = 0; i < tileIdsOnWhichPlayerCanBuildHouses.size(); i++)
        {
            const auto &sameColorTileIdsOnWhichPlayerCanBuild = tileIdsOnWhichPlayerCanBuildHouses[i];
            const Tile &firstTileOfGivenColor = board.getTiles().at(sameColorTileIdsOnWhichPlayerCanBuild[0]);
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) < 6 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost())
            {
                for (int8_t j = 0; j < sameColorTileIdsOnWhichPlayerCanBuild.size(); j++)
                {
                    Tile &tileOnPlayerTriesToBuild =
                        board.getTilesForModification().at(sameColorTileIdsOnWhichPlayerCanBuild[j]);
                    if (tileOnPlayerTriesToBuild.getNumOfHouses() <
                            utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tileOnPlayerTriesToBuild, board) and
                        moneyToSpentAtHouseBuying >= tileOnPlayerTriesToBuild.getHouseCost())
                    {
                        tileOnPlayerTriesToBuild.buildHouse();
                        player.subtractBalance(tileOnPlayerTriesToBuild.getHouseCost());
                        moneyToSpentAtHouseBuying -= tileOnPlayerTriesToBuild.getHouseCost();
                        Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                                      "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
                        logger.logHouseBuying(player, tileOnPlayerTriesToBuild);
                    }
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
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) < 6 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost())
            {
                for (int8_t j = sameColorTileIdsOnWhichPlayerCanBuild.size() - 1; j >= 0; j--)
                {
                    Tile &tileOnPlayerTriesToBuild =
                        board.getTilesForModification().at(sameColorTileIdsOnWhichPlayerCanBuild[j]);
                    if (tileOnPlayerTriesToBuild.getNumOfHouses() <
                            utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tileOnPlayerTriesToBuild, board) and
                        moneyToSpentAtHouseBuying >= tileOnPlayerTriesToBuild.getHouseCost())
                    {
                        tileOnPlayerTriesToBuild.buildHouse();
                        player.subtractBalance(tileOnPlayerTriesToBuild.getHouseCost());
                        moneyToSpentAtHouseBuying -= tileOnPlayerTriesToBuild.getHouseCost();
                        Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                                      "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
                        logger.logHouseBuying(player, tileOnPlayerTriesToBuild);
                    }
                }
            }
        }
    }
}