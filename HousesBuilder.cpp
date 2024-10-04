#include "HousesBuilder.hpp"

void HousesBuilder::tryBuilding(Player &player, Board &board, const Utils &utils)
{
    if (player.getBuyingHousesStrategy() == 0)
    {
        for (const uint8_t ownedTileIdwhereBuildingIsAllowed :
             utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board))
        {
            auto &tile = board.getTilesForModification().at(ownedTileIdwhereBuildingIsAllowed);
            while (player.getCurrentBalance() > tile.getHouseCost() and tile.getNumOfHouses() < 5)
            {
                tile.buildHouse();
                player.subtractBalance(tile.getHouseCost());
            }
        }
    }
}