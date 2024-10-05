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

TEST_F(TestUtils, isChanceTile)
{
    Tile tile1("Chance", 0, {}, 0, 7);
    Tile tile2("Chance", 0, {}, 0, 22);
    Tile tile3("Chance", 0, {}, 0, 36);

    EXPECT_EQ(true, utils.isChanceTile(tile1));
    EXPECT_EQ(true, utils.isChanceTile(tile2));
    EXPECT_EQ(true, utils.isChanceTile(tile3));
}

TEST_F(TestUtils, isCommunityChest)
{
    Tile tile1("CommunityChest", 0, {}, 0, 2);
    Tile tile2("CommunityChest", 0, {}, 0, 17);
    Tile tile3("CommunityChest", 0, {}, 0, 33);

    EXPECT_EQ(true, utils.isCommunityChestTile(tile1));
    EXPECT_EQ(true, utils.isCommunityChestTile(tile2));
    EXPECT_EQ(true, utils.isCommunityChestTile(tile3));
}

TEST_F(TestUtils, isIncomeTax)
{
    Tile tile1("IncomeTax", 0, {}, 0, 4);
    EXPECT_EQ(true, utils.isIncomeTax(tile1));
}

TEST_F(TestUtils, isLuxuryTax)
{
    Tile tile1("LuxuryTax", 350, {}, 0, 38);
    EXPECT_EQ(true, utils.isLuxuryTax(tile1));
}

TEST_F(TestUtils, ExpectTilesToBuildToBe1And3)
{
    Player player(firstPlayerId);
    Board board;
    player.addOwnedTileId(1);
    player.addOwnedTileId(3);
    player.addOwnedTileId(5);

    std::vector<std::vector<uint8_t>> expectedTileIdsOnWhichPlayerCanBuild{{1, 3}};

    EXPECT_EQ(expectedTileIdsOnWhichPlayerCanBuild, utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board));
}

TEST_F(TestUtils, ExpectTilesToBuildToBeNone)
{
    Player player(firstPlayerId);
    Board board;
    player.addOwnedTileId(5);
    player.addOwnedTileId(6);
    player.addOwnedTileId(8);

    std::vector<std::vector<uint8_t>> expectedTileIdsOnWhichPlayerCanBuild{};

    EXPECT_EQ(expectedTileIdsOnWhichPlayerCanBuild, utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board));
}

TEST_F(TestUtils, ExpectTilesToBuildToBeAllLightBlueAndRed)
{
    Player player(firstPlayerId);
    Board board;
    player.addOwnedTileId(5);
    player.addOwnedTileId(6);
    player.addOwnedTileId(8);
    player.addOwnedTileId(9);
    player.addOwnedTileId(21);
    player.addOwnedTileId(23);
    player.addOwnedTileId(24);
    player.addOwnedTileId(25);

    std::vector<std::vector<uint8_t>> expectedTileIdsOnWhichPlayerCanBuild{{6, 8, 9}, {21, 23, 24}};

    EXPECT_EQ(expectedTileIdsOnWhichPlayerCanBuild, utils.getTileIdsOnWhichPlayerCanBuildHouses(player, board));
}

TEST_F(TestUtils, getMaxNumOfHousesThatCanBeBuildOnGivenTileGet1OnBrownTiles)
{
    Board board;
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);
    board.getTilesForModification().at(1).setNumOfHouses(0);
    board.getTilesForModification().at(3).setNumOfHouses(0);

    EXPECT_EQ(1, utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tile, board));
}

TEST_F(TestUtils, getMaxNumOfHousesThatCanBeBuildOnGivenTileGet2OnBrownTiles)
{
    Board board;
    Tile tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);
    board.getTilesForModification().at(1).setNumOfHouses(2);
    board.getTilesForModification().at(3).setNumOfHouses(1);

    EXPECT_EQ(2, utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tile, board));
}

TEST_F(TestUtils, getMaxNumOfHousesThatCanBeBuildOnGivenTileGet5OnBlueTiles)
{
    Board board;
    Tile tile("Property", 400, {50, 200, 600, 1400, 1700, 2000}, 200, 39);
    board.getTilesForModification().at(39).setNumOfHouses(4);
    board.getTilesForModification().at(37).setNumOfHouses(4);

    EXPECT_EQ(5, utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tile, board));
}

TEST_F(TestUtils, getMaxNumOfHousesThatCanBeBuildOnGivenTileGet3OnPinkTiles)
{
    Board board;
    Tile tile("Property", 140, {10, 50, 150, 450, 625, 750}, 100, 13);
    board.getTilesForModification().at(11).setNumOfHouses(2);
    board.getTilesForModification().at(13).setNumOfHouses(2);
    board.getTilesForModification().at(14).setNumOfHouses(3);

    EXPECT_EQ(3, utils.getMaxNumOfHousesThatCanBeBuildOnGivenTile(tile, board));
}

} // namespace ut
