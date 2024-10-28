#include "PlayerRemover.hpp"

#include "Logger.hpp"

void PlayerRemover::remove(std::vector<Player> &players, Player &playerToRemove, Board &board,
                           CommunityChest &communiyChest, Chance &chance, HousesBuilder &housesBuilder)
{
    Logger logger;
    logger.logRemovePlayer(playerToRemove, board);
    for (const uint8_t ownedTileId : playerToRemove.getOwnedTilesIds())
    {
        board.getTilesForModification().at(ownedTileId).setOwnerId(invalidPlayerId);
    }

    uint8_t playerToRemoveTotalNumOfHouses = 0;
    uint8_t playerToRemoveTotalNumOfHotels = 0;
    for (const uint8_t ownedTileId : playerToRemove.getOwnedTilesIds())
    {
        if (board.getTiles().at(ownedTileId).getNumOfHouses() == 5)
        {
            playerToRemoveTotalNumOfHotels++;
        }
        else
        {
            playerToRemoveTotalNumOfHouses += board.getTiles().at(ownedTileId).getNumOfHouses();
        }
        board.getTilesForModification().at(ownedTileId).setNumOfHouses(0);
    }
    housesBuilder.addAvailableHouses(playerToRemoveTotalNumOfHouses);
    housesBuilder.addAvailableHotels(playerToRemoveTotalNumOfHotels);

    if (playerToRemove.hasGetOutOfPrisonChanceCard())
    {
        chance.setIsGetOutOfPrisonCardAvailable(true);
    }

    if (playerToRemove.hasGetOutOfPrisonCommunityChestCard())
    {
        communiyChest.setIsGetOutOfPrisonCardAvailable(true);
    }

    std::vector<Player> newPlayers{};
    for (const auto &oldPlayer : players)
    {
        if (oldPlayer.getId() != playerToRemove.getId())
        {
            newPlayers.push_back(oldPlayer);
        }
    }
    players = newPlayers;
}
