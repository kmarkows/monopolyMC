#include "../Utils.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;

class TestUtils : public ::testing::Test
{
  protected:
    Utils utils;
};

TEST_F(TestUtils, countNumberOfRailroadTiles0)
{
    Player player(firstPlayerId);
    Tile tile("Railroad", 200, {25, 50, 100, 200}, 0, 5);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countNumberOfRailroadTilest2)
{
    Player player(firstPlayerId);
    player.addOwnedTileId(5);
    player.addOwnedTileId(15);
    Tile tile("Railroad", 200, {25, 50, 100, 200}, 0, 5);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 2);
}

TEST_F(TestUtils, countNumberOfRailroadTiles4)
{
    Player player(firstPlayerId);
    player.addOwnedTileId(5);
    player.addOwnedTileId(15);
    player.addOwnedTileId(25);
    player.addOwnedTileId(35);
    Tile tile("Railroad", 200, {25, 50, 100, 200}, 0, 5);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 4);
}

TEST_F(TestUtils, countNumberOfUtilitiesExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Utilities", 150, {4, 10}, 0, 12);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countNumberOfUtilitiesExpect2)
{
    Player player(firstPlayerId);
    Tile tile("Utilities", 150, {4, 10}, 0, 12);
    player.addOwnedTileId(12);
    player.addOwnedTileId(28);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 2);
}

TEST_F(TestUtils, countSameBrownTilesNumberOfExpect2)
{
    Player player(firstPlayerId);
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);
    player.addOwnedTileId(1);
    player.addOwnedTileId(3);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 2);
}

TEST_F(TestUtils, countSameBrownTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSameLightBlueTilesNumberOfExpect3)
{
    Player player(firstPlayerId);
    Tile tile("Property", 100, {6, 30, 90, 270, 400, 550}, 50, 6);
    player.addOwnedTileId(6);
    player.addOwnedTileId(8);
    player.addOwnedTileId(9);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 3);
}

TEST_F(TestUtils, countSameLightBlueTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 100, {6, 30, 90, 270, 400, 550}, 50, 6);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSamePinkTilesNumberOfExpect3)
{
    Player player(firstPlayerId);
    Tile tile("Property", 140, {10, 50, 150, 450, 625, 750}, 100, 11);
    player.addOwnedTileId(11);
    player.addOwnedTileId(13);
    player.addOwnedTileId(14);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 3);
}

TEST_F(TestUtils, countSamePinkTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 140, {10, 50, 150, 450, 625, 750}, 100, 11);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSameOrangeTilesNumberOfExpect3)
{
    Player player(firstPlayerId);
    Tile tile("Property", 180, {14, 70, 200, 550, 750, 950}, 100, 16);
    player.addOwnedTileId(16);
    player.addOwnedTileId(18);
    player.addOwnedTileId(19);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 3);
}

TEST_F(TestUtils, countSameOrangeTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 180, {14, 70, 200, 550, 750, 950}, 100, 16);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSameRedTilesNumberOfExpect3)
{
    Player player(firstPlayerId);
    Tile tile("Property", 220, {18, 90, 250, 700, 875, 1050}, 150, 21);
    player.addOwnedTileId(21);
    player.addOwnedTileId(23);
    player.addOwnedTileId(24);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 3);
}

TEST_F(TestUtils, countSameRedTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 220, {18, 90, 250, 700, 875, 1050}, 150, 21);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSameYellowTilesNumberOfExpect3)
{
    Player player(firstPlayerId);
    Tile tile("Property", 260, {22, 110, 330, 800, 975, 1150}, 150, 26);
    player.addOwnedTileId(26);
    player.addOwnedTileId(27);
    player.addOwnedTileId(29);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 3);
}

TEST_F(TestUtils, countSameYellowTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 260, {22, 110, 330, 800, 975, 1150}, 150, 26);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSameGreenTilesNumberOfExpect3)
{
    Player player(firstPlayerId);
    Tile tile("Property", 300, {26, 130, 390, 900, 1100, 1275}, 200, 31);
    player.addOwnedTileId(31);
    player.addOwnedTileId(32);
    player.addOwnedTileId(34);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 3);
}

TEST_F(TestUtils, countSameGreenTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 300, {26, 130, 390, 900, 1100, 1275}, 200, 31);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

TEST_F(TestUtils, countSameBlueTilesNumberOfExpect2)
{
    Player player(firstPlayerId);
    Tile tile("Property", 350, {35, 175, 500, 1100, 1300, 1500}, 200, 37);
    player.addOwnedTileId(37);
    player.addOwnedTileId(39);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 2);
}

TEST_F(TestUtils, countSameBlueTilesNumberOfExpect0)
{
    Player player(firstPlayerId);
    Tile tile("Property", 350, {35, 175, 500, 1100, 1300, 1500}, 200, 37);

    EXPECT_EQ(utils.getNumOfTilesOfEachTypeOwnedByPlayer(player, tile), 0);
}

} // namespace ut
