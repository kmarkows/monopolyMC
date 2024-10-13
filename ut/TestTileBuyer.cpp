#include "../TileBuyer.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 1;
constexpr int startingBalance = 1500;

class TestTileBuyer : public ::testing::Test
{
  protected:
    TileBuyer tileBuyer;
    Player player{firstPlayerId};
    Board board;
    Utils utils;
};

TEST_F(TestTileBuyer, PlayerCurrTile1BuysTileId1BasicStrategy)
{
    player.setBuyingTilesStrategy({1.0, 1.0, 0.5});
    player.setBalance(startingBalance);
    player.setCurrTile(1);

    tileBuyer.tryBuying(player, board, utils);

    std::vector<uint8_t> ownedTileIds{1};
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), firstPlayerId);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTileIds);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - board.getTiles().at(1).getCost());
}

TEST_F(TestTileBuyer, PlayerCurrTile1DoesNotBuyTileId1NotBasicStrategyPrioSecondHalf)
{
    player.setBuyingTilesStrategy({2.0, 1.0, 0.5});
    player.setBalance(200);
    player.setCurrTile(1);

    tileBuyer.tryBuying(player, board, utils);

    std::vector<uint8_t> ownedTileIds{};
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), invalidPlayerId);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTileIds);
    EXPECT_EQ(player.getCurrentBalance(), 200);
}

TEST_F(TestTileBuyer, PlayerCurrTile1BuysTileId1NotBasicStrategyPrioSecondHalfButPlayerHasAlreadyOtherTileOfSameColor)
{
    player.setBuyingTilesStrategy({2.0, 1.0, 0.5});
    player.setBalance(200);
    player.setCurrTile(1);
    player.addOwnedTileId(3);

    tileBuyer.tryBuying(player, board, utils);

    std::vector<uint8_t> ownedTileIds{1, 3};
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), firstPlayerId);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTileIds);
    EXPECT_EQ(player.getCurrentBalance(), 200 - board.getTiles().at(1).getCost());
}

TEST_F(TestTileBuyer, PlayerCurrTile1BuysTileId1NotBasicStrategyPrioFirstHalf)
{
    player.setBuyingTilesStrategy({1.0, 2.0, 0.5});
    player.setBalance(200);
    player.setCurrTile(1);

    tileBuyer.tryBuying(player, board, utils);

    std::vector<uint8_t> ownedTileIds{1};
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), firstPlayerId);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTileIds);
    EXPECT_EQ(player.getCurrentBalance(), 200 - board.getTiles().at(1).getCost());
}

TEST_F(TestTileBuyer, PlayerCurrTile1DoesNotBuyTileId1BasicStrategyNoEnoughMoneyToSpendOnTileBuying)
{
    player.setBuyingTilesStrategy({1.0, 2.0, 0.25});
    player.setBalance(200);
    player.setCurrTile(1);

    tileBuyer.tryBuying(player, board, utils);

    std::vector<uint8_t> ownedTileIds{};
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), invalidPlayerId);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTileIds);
    EXPECT_EQ(player.getCurrentBalance(), 200);
}

} // namespace ut