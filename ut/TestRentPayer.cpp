#include "../RentPayer.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 1;
constexpr int startingBalance = 1500;

class TestRentPayer : public ::testing::Test
{
  protected:
    Utils utils;
    Player player{firstPlayerId};
    Player owner{secondPlayerId};
    uint8_t diceResult = 0;
};

TEST_F(TestRentPayer, TestFirstPlayerLandsOnTileId1NoHousesAreBuiltAndPaysRentToSecondPlayer)
{
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 2);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 2);
}

TEST_F(TestRentPayer, TestFirstPlayerLandsOnTileId1FourHousesAreBuiltAndPaysRentToSecondPlayer)
{
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);
    tile.setNumOfHouses(4);

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 160);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 160);
}

TEST_F(TestRentPayer, TestFirstPlayerLandsOnTileId1HotelIdBuiltAndPaysRentToSecondPlayer)
{
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);
    tile.setNumOfHouses(5);

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 250);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 250);
}

TEST_F(TestRentPayer, TestFirstPlayerLandsOnRailroadTile5AndSecondPlayerOwnsThatTileWhichIsOnlyOneRailroad)
{
    Tile tile("Railroad", 200, {25, 50, 100, 200}, 0, 5);
    owner.addOwnedTileId(tile.getId());

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 25);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 25);
}

TEST_F(TestRentPayer, TestFirstPlayerLandsOnRailroadTile15AndSecondPlayerOwnsThatTileAndTwoOtherRailroads)
{
    Tile tile("Railroad", 200, {25, 50, 100, 200}, 0, 15);
    owner.addOwnedTileId(5);
    owner.addOwnedTileId(tile.getId());
    owner.addOwnedTileId(25);

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 100);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 100);
}

TEST_F(TestRentPayer, TestFirstPlayerLandsOnRailroadTile25AndSecondPlayerOwnsAllRailroads)
{
    Tile tile("Railroad", 200, {25, 50, 100, 200}, 0, 25);
    owner.addOwnedTileId(5);
    owner.addOwnedTileId(15);
    owner.addOwnedTileId(tile.getId());
    owner.addOwnedTileId(35);

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 200);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 200);
}

TEST_F(TestRentPayer, TestFirstPlayerRollsSum10AndLandsOnUtilitiesTileId12AndSecondPlayerOwnsOneUtilities)
{
    Tile tile("Utilities", 150, {4, 10}, 0, 12);
    owner.addOwnedTileId(tile.getId());
    diceResult = 10;

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 40);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 40);
}

TEST_F(TestRentPayer, TestFirstPlayerRollsSum9AndLandsOnUtilitiesTileId28AndSecondPlayerOwnsThreeUtilities)
{
    Tile tile1("Utilities", 150, {4, 10}, 0, 12);
    Tile tile2("Utilities", 150, {4, 10}, 0, 28);
    owner.addOwnedTileId(tile1.getId());
    owner.addOwnedTileId(tile2.getId());
    diceResult = 9;

    RentPayer rentPayer(utils);
    rentPayer.payRent(player, owner, tile2, diceResult);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 90);
    EXPECT_EQ(owner.getCurrentBalance(), startingBalance + 90);
}

} // namespace ut