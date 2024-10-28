#include "HousesBuilder.hpp"
#include "Logger.hpp"

// TO DO refactoring

void HousesBuilder::tryBuilding(Player &player, Board &board, const Utils &utils)
{
    moneyToSpentAtHouseBuying = player.getBuyingHousesStrategy().moneyToSpentAtHouseBuying * player.getCurrentBalance();
    Logger logger;
    logger.logTryHouseBuying(player, availableHouses, availableHotels);
    if (player.getBuyingHousesStrategy().colorPriority == 0)
    {
        const auto &tileIdsOnWhichPlayerCanBuildHouses = utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board);
        for (int8_t i = 0; i < tileIdsOnWhichPlayerCanBuildHouses.size(); i++)
        {
            const auto &sameColorTileIdsOnWhichPlayerCanBuild = tileIdsOnWhichPlayerCanBuildHouses[i];
            const Tile &firstTileOfGivenColor = board.getTiles().at(sameColorTileIdsOnWhichPlayerCanBuild[0]);
            while (utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(firstTileOfGivenColor, board) < 5 and
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost() and availableHouses > 0)
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
                   player.getBuyingHousesStrategy().isBuyingHotels and availableHotels > 0)
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
                   moneyToSpentAtHouseBuying >= firstTileOfGivenColor.getHouseCost() and availableHouses > 0)
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
                   player.getBuyingHousesStrategy().isBuyingHotels and availableHotels > 0)
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
        Logger logger;
        logger.logHouseBuying(player, tileOnPlayerTriesToBuild, availableHouses, availableHotels);
    }
}

void HousesBuilder::buildHotels(Player &player, Tile &tileOnPlayerTriesToBuild, Board &board, const Utils &utils)
{

    if (tileOnPlayerTriesToBuild.getNumOfHouses() <
            utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tileOnPlayerTriesToBuild, board) and
        moneyToSpentAtHouseBuying >= tileOnPlayerTriesToBuild.getHouseCost() and availableHotels > 0)
    {
        tileOnPlayerTriesToBuild.buildHouse();
        player.subtractBalance(tileOnPlayerTriesToBuild.getHouseCost());
        moneyToSpentAtHouseBuying -= tileOnPlayerTriesToBuild.getHouseCost();
        availableHotels--;
        availableHouses += 4;
        Logger logger;
        logger.logHouseBuying(player, tileOnPlayerTriesToBuild, availableHouses, availableHotels);
    }
}

void HousesBuilder::addAvailableHouses(const uint8_t availableHousesToAdd)
{
    availableHouses += availableHousesToAdd;
}

const uint8_t HousesBuilder::getAvailableHouses() const
{
    return availableHouses;
}

void HousesBuilder::setAvailableHouses(const uint8_t availableHousesToSet)
{
    availableHouses = availableHousesToSet;
}

void HousesBuilder::addAvailableHotels(const uint8_t availableHotelsToAdd)
{
    availableHotels += availableHotelsToAdd;
}

const uint8_t HousesBuilder::getAvailableHotels() const
{
    return availableHotels;
}

void HousesBuilder::setAvailableHotels(const uint8_t availableHotelsToSet)
{
    availableHotels = availableHotelsToSet;
}
