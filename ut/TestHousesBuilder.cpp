#include "../HousesBuilder.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr int startingBalance = 1500;

class TestHousesBuilder : public ::testing::Test
{
  protected:
    HousesBuilder housesBuilder;
    Board board;
    Utils utils;
};

TEST_F(TestHousesBuilder, buildAllHouseOnTile1And3StartingWithNoHouses)
{
    Player player(firstPlayerId);
    player.setBuyingHousesStrategy(0);
    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 5);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 5);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 2 * 5 * 50);
}

} // namespace ut
