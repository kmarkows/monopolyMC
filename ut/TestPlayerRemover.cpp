#include "../PlayerRemover.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t invalidPlayerId = 0;
constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 2;
constexpr uint8_t thirdPlayerId = 3;

class TestPlayerRemover : public ::testing::Test
{
  protected:
    PlayerRemover playerRemover;
    std::vector<Player> players;
    Player player{firstPlayerId};
    Board board;
    CommunityChest communityChest;
    Chance chance;
    HousesBuilder housesBuilder;
};

TEST_F(TestPlayerRemover, ThreePlayersInGameFirstIsRemoved)
{
    Player player2(secondPlayerId);
    Player player3(thirdPlayerId);

    board.getTilesForModification().at(1).setOwnerId(firstPlayerId);
    player.addOwnedTileId(1);
    board.getTilesForModification().at(3).setOwnerId(firstPlayerId);
    player.addOwnedTileId(3);
    players.push_back(player);

    players.push_back(player2);
    players.push_back(player3);

    playerRemover.remove(players, player, board, communityChest, chance, housesBuilder);

    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), 0);
    EXPECT_EQ(board.getTiles().at(3).getOwnerId(), 0);
}

TEST_F(TestPlayerRemover, ThreePlayersInGameThirdIsRemoved)
{
    Player player2(secondPlayerId);
    Player player3(thirdPlayerId);

    board.getTilesForModification().at(1).setOwnerId(thirdPlayerId);
    player3.addOwnedTileId(1);
    board.getTilesForModification().at(3).setOwnerId(thirdPlayerId);
    player3.addOwnedTileId(3);

    players.push_back(player);
    players.push_back(player2);
    players.push_back(player3);

    playerRemover.remove(players, player3, board, communityChest, chance, housesBuilder);

    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), 0);
    EXPECT_EQ(board.getTiles().at(3).getOwnerId(), 0);
}

TEST_F(TestPlayerRemover, ThreePlayersInGameSecondIsRemoved)
{
    Player player2(secondPlayerId);
    Player player3(thirdPlayerId);

    board.getTilesForModification().at(1).setOwnerId(secondPlayerId);
    player2.addOwnedTileId(1);
    board.getTilesForModification().at(3).setOwnerId(secondPlayerId);
    player2.addOwnedTileId(3);

    players.push_back(player);
    players.push_back(player2);
    players.push_back(player3);

    playerRemover.remove(players, player2, board, communityChest, chance, housesBuilder);

    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), 0);
    EXPECT_EQ(board.getTiles().at(3).getOwnerId(), 0);
}

TEST_F(TestPlayerRemover, ThreePlayersInGameFirstIsRemovedGetOutOfPrisonCardsAreReturned)
{
    Player player2(secondPlayerId);
    Player player3(thirdPlayerId);

    player.acquireGetOutOfPrisonChanceCard();
    chance.setIsGetOutOfPrisonCardAvailable(false);
    player.acquireGetOutOfPrisonCommunityChestCard();
    communityChest.setIsGetOutOfPrisonCardAvailable(false);

    players.push_back(player);
    players.push_back(player2);
    players.push_back(player3);

    playerRemover.remove(players, player, board, communityChest, chance, housesBuilder);

    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(chance.getIsGetOutOfPrisonCardAvailable(), true);
    EXPECT_EQ(communityChest.getIsGetOutOfPrisonCardAvailable(), true);
}

TEST_F(TestPlayerRemover, playerHasTwoTilesOnOneHotelAndOnSecond4Houses)
{
    player.addOwnedTileId(1);
    board.getTilesForModification().at(1).setNumOfHouses(5);
    player.addOwnedTileId(3);
    board.getTilesForModification().at(3).setNumOfHouses(4);

    player.addOwnedTileId(6);
    board.getTilesForModification().at(6).setNumOfHouses(2);
    player.addOwnedTileId(8);
    board.getTilesForModification().at(8).setNumOfHouses(2);
    player.addOwnedTileId(9);
    board.getTilesForModification().at(9).setNumOfHouses(2);

    Player player2(secondPlayerId);
    Player player3(thirdPlayerId);

    players.push_back(player);
    players.push_back(player2);
    players.push_back(player3);

    housesBuilder.setAvailableHouses(10);
    housesBuilder.setAvailableHotels(5);

    playerRemover.remove(players, player, board, communityChest, chance, housesBuilder);

    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(housesBuilder.getAvailableHouses(), 20);
    EXPECT_EQ(housesBuilder.getAvailableHotels(), 6);
    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 0);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 0);
}

} // namespace ut