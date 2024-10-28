#include "../Trader.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 2;
constexpr uint8_t thirdPlayerId = 3;
constexpr int startingBalance = 1500;

class TestTrader : public ::testing::Test
{
  protected:
    Trader trader;
    Utils utils;
    Board board;
    Player buyer{firstPlayerId};
    std::vector<Player> players{};
    uint8_t diceResult = 0;
};

TEST_F(TestTrader, PlayerBuysTile1FromSecondPlayer)
{
    buyer.setBalance(startingBalance);
    buyer.addOwnedTileId(3);
    players.push_back(buyer);

    Player player2(secondPlayerId);
    player2.setBalance(startingBalance);
    player2.addOwnedTileId(1);
    players.push_back(player2);

    board.getTilesForModification().at(1).setOwnerId(secondPlayerId);
    board.getTilesForModification().at(3).setOwnerId(firstPlayerId);

    trader.trade(buyer, players, board, utils);

    std::vector<uint8_t> buyerTileIds{1, 3};
    std::vector<uint8_t> sellerTileIds{};
    EXPECT_EQ(buyer.getOwnedTilesIds(), buyerTileIds);
    EXPECT_EQ(buyer.getCurrentBalance(), startingBalance - 118);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getOwnedTilesIds(), sellerTileIds);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getCurrentBalance(), startingBalance + 118);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), firstPlayerId);
}

TEST_F(TestTrader, PlayerTrieSToBuyTile1FromSecondPlayerButHasNotEnoughMoney)
{
    buyer.setBalance(200);
    buyer.addOwnedTileId(3);
    players.push_back(buyer);

    Player player2(secondPlayerId);
    player2.setBalance(startingBalance);
    player2.addOwnedTileId(1);
    players.push_back(player2);

    board.getTilesForModification().at(1).setOwnerId(secondPlayerId);
    board.getTilesForModification().at(3).setOwnerId(firstPlayerId);

    trader.trade(buyer, players, board, utils);

    std::vector<uint8_t> buyerTileIds{3};
    std::vector<uint8_t> sellerTileIds{1};
    EXPECT_EQ(buyer.getOwnedTilesIds(), buyerTileIds);
    EXPECT_EQ(buyer.getCurrentBalance(), 200);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getOwnedTilesIds(), sellerTileIds);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getCurrentBalance(), startingBalance);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), secondPlayerId);
}

TEST_F(TestTrader, PlayerTrieSToBuyTile1FromSecondPlayerButSellerHasBigSellingRatio)
{
    buyer.setBalance(300);
    buyer.addOwnedTileId(3);
    players.push_back(buyer);

    Player player2(secondPlayerId);
    player2.setBalance(startingBalance);
    player2.setTradingStrategy({0, 1.0f, 2.0f, 0.5f});
    player2.addOwnedTileId(1);
    players.push_back(player2);

    board.getTilesForModification().at(1).setOwnerId(secondPlayerId);
    board.getTilesForModification().at(3).setOwnerId(firstPlayerId);

    trader.trade(buyer, players, board, utils);

    std::vector<uint8_t> buyerTileIds{3};
    std::vector<uint8_t> sellerTileIds{1};
    EXPECT_EQ(buyer.getOwnedTilesIds(), buyerTileIds);
    EXPECT_EQ(buyer.getCurrentBalance(), 300);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getOwnedTilesIds(), sellerTileIds);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getCurrentBalance(), startingBalance);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), secondPlayerId);
}

TEST_F(TestTrader, PlayerBuysTile1FromSecondPlayerBuyerAndSellerHasBigFactors)
{
    buyer.setBalance(300);
    buyer.setTradingStrategy({0, 2.0f, 1.0f, 0.8f});
    buyer.addOwnedTileId(3);
    players.push_back(buyer);

    Player player2(secondPlayerId);
    player2.setBalance(startingBalance);
    player2.setTradingStrategy({0, 1.0f, 2.0f, 0.5f});
    player2.addOwnedTileId(1);
    players.push_back(player2);

    board.getTilesForModification().at(1).setOwnerId(secondPlayerId);
    board.getTilesForModification().at(3).setOwnerId(firstPlayerId);

    trader.trade(buyer, players, board, utils);

    std::vector<uint8_t> buyerTileIds{1, 3};
    std::vector<uint8_t> sellerTileIds{};
    EXPECT_EQ(buyer.getOwnedTilesIds(), buyerTileIds);
    EXPECT_EQ(buyer.getCurrentBalance(), 300 - 237);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getOwnedTilesIds(), sellerTileIds);
    EXPECT_EQ(utils.getPlayerById(players, secondPlayerId).getCurrentBalance(), startingBalance + 237);
    EXPECT_EQ(board.getTiles().at(1).getOwnerId(), firstPlayerId);
}

} // namespace ut