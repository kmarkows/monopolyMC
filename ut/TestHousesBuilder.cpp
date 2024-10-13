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

    uint8_t colorPrio{0};
    float moneyToSpentAtHouseBuying{0.0f};
    bool isBuyingHotels{true};
};

TEST_F(TestHousesBuilder, build3HousesOnBrownTilesStartingWithNoHouses)
{
    Player player(firstPlayerId);
    colorPrio = 0;
    moneyToSpentAtHouseBuying = 0.1f;
    isBuyingHotels = true;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 2);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 1);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 3 * 50);
}

TEST_F(TestHousesBuilder, build6HousesOnBrownTilesStartingWithNoHousesBuild)
{
    Player player(firstPlayerId);
    colorPrio = 0;
    moneyToSpentAtHouseBuying = 0.2f;
    isBuyingHotels = true;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 3);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 3);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 6 * 50);
}

TEST_F(TestHousesBuilder, buildAllHousesOnBrownTilesStartingWithNoHousesBuild)
{
    Player player(firstPlayerId);
    colorPrio = 0;
    moneyToSpentAtHouseBuying = 0.4f;
    isBuyingHotels = true;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 5);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 5);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 10 * 50);
}

TEST_F(TestHousesBuilder, buildAllHousesOnBrownButNoHotelsTilesStartingWithNoHousesBuild)
{
    Player player(firstPlayerId);
    colorPrio = 0;
    moneyToSpentAtHouseBuying = 0.4f;
    isBuyingHotels = false;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 4);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 4);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 8 * 50);
}

TEST_F(TestHousesBuilder, buildAllHousesOnBrownAnd1OnPinkTilesStartingWithNoHousesBuild)
{
    Player player(firstPlayerId);
    colorPrio = 0;
    moneyToSpentAtHouseBuying = 0.4f;
    isBuyingHotels = true;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.addOwnedTileId(11);
    player.addOwnedTileId(13);
    player.addOwnedTileId(14);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 5);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 5);
    EXPECT_EQ(board.getTiles().at(11).getNumOfHouses(), 1);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 10 * 50 - 1 * 100);
}

TEST_F(TestHousesBuilder, buildAllHousesOnBrownAnd4OnPinkTilesStartingWithNoHousesBuild)
{
    Player player(firstPlayerId);
    colorPrio = 0;
    moneyToSpentAtHouseBuying = 0.6f;
    isBuyingHotels = true;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.addOwnedTileId(11);
    player.addOwnedTileId(13);
    player.addOwnedTileId(14);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 5);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 5);
    EXPECT_EQ(board.getTiles().at(11).getNumOfHouses(), 2);
    EXPECT_EQ(board.getTiles().at(13).getNumOfHouses(), 1);
    EXPECT_EQ(board.getTiles().at(14).getNumOfHouses(), 1);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 10 * 50 - 4 * 100);
}

TEST_F(TestHousesBuilder, buildNoneHousesOnBrownAnd9OnPinkTilesStartingWithNoHousesBuild)
{
    Player player(firstPlayerId);
    colorPrio = 1;
    moneyToSpentAtHouseBuying = 0.6f;
    isBuyingHotels = true;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.addOwnedTileId(11);
    player.addOwnedTileId(13);
    player.addOwnedTileId(14);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 0);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 0);
    EXPECT_EQ(board.getTiles().at(11).getNumOfHouses(), 3);
    EXPECT_EQ(board.getTiles().at(13).getNumOfHouses(), 3);
    EXPECT_EQ(board.getTiles().at(14).getNumOfHouses(), 3);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 9 * 100);
}

TEST_F(TestHousesBuilder, buildNoneHousesOnBrownAnd9OnPinkTilesStartingWithNoHousesBuildHousesButNoHotels)
{
    Player player(firstPlayerId);
    colorPrio = 1;
    moneyToSpentAtHouseBuying = 0.9f;
    isBuyingHotels = false;
    player.setBuyingHousesStrategy({colorPrio, moneyToSpentAtHouseBuying, isBuyingHotels});

    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.addOwnedTileId(11);
    player.addOwnedTileId(13);
    player.addOwnedTileId(14);
    player.setBalance(startingBalance);

    housesBuilder.tryBuilding(player, board, utils);

    EXPECT_EQ(board.getTiles().at(1).getNumOfHouses(), 1);
    EXPECT_EQ(board.getTiles().at(3).getNumOfHouses(), 2);
    EXPECT_EQ(board.getTiles().at(11).getNumOfHouses(), 4);
    EXPECT_EQ(board.getTiles().at(13).getNumOfHouses(), 4);
    EXPECT_EQ(board.getTiles().at(14).getNumOfHouses(), 4);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 12 * 100 - 3 * 50);
}

} // namespace ut
