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

    playerRemover.remove(players, player, board);

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

    playerRemover.remove(players, player3, board);

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

    playerRemover.remove(players, player2, board);

    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), 0);
    EXPECT_EQ(board.getTiles().at(3).getOwnerId(), 0);
}

} // namespace ut