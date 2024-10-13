#include "PlayerRemover.hpp"

#include "Logger.hpp"

void PlayerRemover::remove(std::vector<Player> &players, Player &playerToRemove, Board &board)
{
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logRemovePlayer(playerToRemove);

    for (const uint8_t ownedTileId : playerToRemove.getOwnedTilesIds())
    {
        board.getTilesForModification().at(ownedTileId).setOwnerId(invalidPlayerId);
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
