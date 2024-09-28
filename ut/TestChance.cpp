#include "../Chance.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 2;

class TestChance : public ::testing::Test
{
  protected:
    Player player{firstPlayerId};
    Game game;
    Chance chance;
    MockDiceThrower<4, 3> mockDiceThrower;
    uint8_t currentlyTestedCard;
};

TEST_F(TestChance, TestGoToStartFieldCardId0)
{
    currentlyTestedCard = 0;

    const uint8_t randomNotStartTile = 15;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTile);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 0);
}

TEST_F(TestChance, TestGoToTile24AndPassStartCardId1)
{
    currentlyTestedCard = 1;

    const uint8_t randomNotStartTileAfter24 = 27;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter24);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 24);
}

TEST_F(TestChance, TestGoToTile24AndNotPassStartCardId1)
{
    currentlyTestedCard = 1;
    const uint8_t randomNotStartTileBefore24 = 21;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore24);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTile(), 24);
}

TEST_F(TestChance, TestGoToTile11AndPassStartCardId2)
{
    currentlyTestedCard = 2;

    const uint8_t randomNotStartTileAfter11 = 20;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter11);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 11);
}

TEST_F(TestChance, TestGoToTile11AndNotPassStartCardId2)
{
    currentlyTestedCard = 2;

    const uint8_t randomNotStartTileBefore11 = 9;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore11);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTile(), 11);
}

TEST_F(TestChance, TestGoToTile12FromTile6AndPlayerIsOwnerNothingHappensCardId3)
{
    currentlyTestedCard = 3;

    const uint8_t waterUtilsTileId = 12;
    const uint8_t tileClosestToWaterUtilsThanElectricityUtils = 6;
    player.setCurrTile(tileClosestToWaterUtilsThanElectricityUtils);
    player.setBalance(startingBalance);
    player.addOwnedTileId(waterUtilsTileId);
    game.getBoardDataForModification().getTilesForModification().at(waterUtilsTileId).setOwnerId(firstPlayerId);
    game.enableBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), waterUtilsTileId);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
}

TEST_F(TestChance, TestGoToTile28FromTile6AndPlayerIsOwnerNothingHappensCardId3)
{
    currentlyTestedCard = 3;

    const uint8_t electricityUtilsTileId = 28;
    const uint8_t tileClosestToElectricityUtilsThanWaterUtils = 22;
    player.setCurrTile(tileClosestToElectricityUtilsThanWaterUtils);
    player.setBalance(startingBalance);
    player.addOwnedTileId(electricityUtilsTileId);
    game.getBoardDataForModification().getTilesForModification().at(electricityUtilsTileId).setOwnerId(firstPlayerId);
    game.enableBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), electricityUtilsTileId);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
}

TEST_F(TestChance, TestGoToTile12FromTile6AndPlayerBuysThatTileCardId3)
{
    currentlyTestedCard = 3;

    const uint8_t waterUtilsTileId = 12;
    const uint8_t tileClosestToWaterUtilsThanElectricityUtils = 6;
    player.setCurrTile(tileClosestToWaterUtilsThanElectricityUtils);
    player.setBalance(startingBalance);
    game.enableBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    const std::vector<uint8_t> ownedTilesIds{waterUtilsTileId};
    EXPECT_EQ(player.getCurrTile(), waterUtilsTileId);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 150);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(waterUtilsTileId).getOwnerId(), firstPlayerId);
}

TEST_F(TestChance, TestGoToTile12FromTile6AndTileIsAlreadyOwnedSoPlayerPays10TimesTheRollCardId3)
{
    currentlyTestedCard = 3;

    const uint8_t waterUtilsTileId = 12;
    const uint8_t tileClosestToWaterUtilsThanElectricityUtils = 6;
    player.setCurrTile(tileClosestToWaterUtilsThanElectricityUtils);
    player.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);
    game.getBoardDataForModification().getTilesForModification().at(waterUtilsTileId).setOwnerId(secondPlayerId);

    Player player2(secondPlayerId);
    game.getPlayersDataForManipulation().push_back(player2);
    game.getPlayersDataForManipulation().at(secondPlayerId - 1).setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), waterUtilsTileId);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 70);
    EXPECT_EQ(game.getPlayersData().at(secondPlayerId - 1).getCurrentBalance(), startingBalance + 70);
}

TEST_F(TestChance, TestGoToTile5FromTile6AndPlayerIsOwnerNothingHappensCardId4)
{
    currentlyTestedCard = 4;

    const uint8_t closestRailway = 5;
    const uint8_t tileClosestToRailroad5Tile = 6;
    player.setCurrTile(tileClosestToRailroad5Tile);
    player.setBalance(startingBalance);
    player.addOwnedTileId(closestRailway);
    game.getBoardDataForModification().getTilesForModification().at(closestRailway).setOwnerId(firstPlayerId);
    game.enableBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
}

TEST_F(TestChance, TestGoToTile5FromTile6AndPlayerBuysThatTileCardId4)
{
    currentlyTestedCard = 4;

    const uint8_t closestRailway = 5;
    const uint8_t tileClosestToRailroad5Tile = 6;
    player.setCurrTile(tileClosestToRailroad5Tile);
    player.setBalance(startingBalance);
    game.enableBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    const std::vector<uint8_t> ownedTilesIds{closestRailway};
    EXPECT_EQ(player.getCurrTile(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 200);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(closestRailway).getOwnerId(), firstPlayerId);
}

TEST_F(TestChance, TestGoToTile5FromTile6AndPlayerPaysAnotherPlayerWhoHasOnlyOneRailroadTileCardId4)
{
    currentlyTestedCard = 4;

    const uint8_t closestRailway = 5;
    const uint8_t tileClosestToRailroad5Tile = 6;
    player.setCurrTile(tileClosestToRailroad5Tile);
    player.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);

    Player player2(secondPlayerId);
    player.addOwnedTileId(closestRailway);
    game.getBoardDataForModification().getTilesForModification().at(closestRailway).setOwnerId(secondPlayerId);
    game.getPlayersDataForManipulation().push_back(player2);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 25);
}

TEST_F(TestChance, TestGetDividend50CardId5)
{
    currentlyTestedCard = 5;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 50);
}

TEST_F(TestChance, TestAcquireGetOutOfPrisonCardCardId6)
{
    currentlyTestedCard = 6;

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.hasGetOutOfPrisonCard(), true);
}

TEST_F(TestChance, TestGoBack3TilesCardId7)
{
    currentlyTestedCard = 7;
    const uint8_t randomChanceTile = 7;
    player.setCurrTile(randomChanceTile);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), 7 - 3);
}

TEST_F(TestChance, TestGoToJailCardCardId8)
{
    currentlyTestedCard = 8;
    const uint8_t randomTile = 7;
    player.setCurrTile(randomTile);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), 10);
    EXPECT_EQ(player.isInPrison(), true);
}

TEST_F(TestChance, TestGeneralRepairsPay25ForEveryHouseAnd100ForHotelCardId9)
{
    currentlyTestedCard = 9;
    player.setBalance(startingBalance);

    game.getBoardDataForModification().getTilesForModification().at(1).setOwnerId(firstPlayerId);
    player.addOwnedTileId(1);
    game.getBoardDataForModification().getTilesForModification().at(1).setNumOfHouses(5);
    game.getBoardDataForModification().getTilesForModification().at(3).setOwnerId(firstPlayerId);
    player.addOwnedTileId(3);
    game.getBoardDataForModification().getTilesForModification().at(3).setNumOfHouses(2);
    game.getBoardDataForModification().getTilesForModification().at(6).setOwnerId(firstPlayerId);
    player.addOwnedTileId(6);
    game.getBoardDataForModification().getTilesForModification().at(6).setNumOfHouses(0);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - (2 * 25 + 100));
}

TEST_F(TestChance, TestGoToTile5AndPassStartCardId10)
{
    currentlyTestedCard = 10;
    const uint8_t randomNotStartTileAfter5 = 6;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter5);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 5);
}

TEST_F(TestChance, TestGoToTile11AndNotPassStartCardId10)
{
    currentlyTestedCard = 10;
    const uint8_t randomNotStartTileBefore5 = 4;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore5);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTile(), 5);
}

TEST_F(TestChance, TestPayPoorTax15CardId11)
{
    currentlyTestedCard = 11;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 15);
}

TEST_F(TestChance, TestAdvanceToTile39CardId12)
{
    currentlyTestedCard = 12;
    const uint8_t randomTile = 6;
    player.setCurrTile(randomTile);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), 39);
}

TEST_F(TestChance, TestPayEveryPlayer50CardId13)
{
    currentlyTestedCard = 13;
    Player player2(2);
    Player player3(3);
    player.setBalance(startingBalance);
    player2.setBalance(startingBalance);
    player3.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);
    game.getPlayersDataForManipulation().push_back(player2);
    game.getPlayersDataForManipulation().push_back(player3);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 2 * 50);
    EXPECT_EQ(game.getPlayersData().at(1).getCurrentBalance(), startingBalance + 50);
    EXPECT_EQ(game.getPlayersData().at(2).getCurrentBalance(), startingBalance + 50);
}

TEST_F(TestChance, TestGet150CardId14)
{
    currentlyTestedCard = 14;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 150);
}

} // namespace ut
