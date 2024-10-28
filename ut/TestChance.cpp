#include "../Chance.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 2;
constexpr uint8_t thirdPlayerId = 3;

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
    EXPECT_EQ(player.getCurrTileId(), 0);
}

TEST_F(TestChance, TestGoToTile24AndPassStartCardId1)
{
    currentlyTestedCard = 1;

    const uint8_t randomNotStartTileAfter24 = 27;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter24);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTileId(), 24);
}

TEST_F(TestChance, TestGoToTile24AndNotPassStartCardId1)
{
    currentlyTestedCard = 1;
    const uint8_t randomNotStartTileBefore24 = 21;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore24);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTileId(), 24);
}

TEST_F(TestChance, TestGoToTile11AndPassStartCardId2)
{
    currentlyTestedCard = 2;

    const uint8_t randomNotStartTileAfter11 = 20;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter11);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTileId(), 11);
}

TEST_F(TestChance, TestGoToTile11AndNotPassStartCardId2)
{
    currentlyTestedCard = 2;

    const uint8_t randomNotStartTileBefore11 = 9;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore11);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTileId(), 11);
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
    game.enableTilesBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), waterUtilsTileId);
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
    game.enableTilesBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), electricityUtilsTileId);
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
    game.enableTilesBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    const std::vector<uint8_t> ownedTilesIds{waterUtilsTileId};
    EXPECT_EQ(player.getCurrTileId(), waterUtilsTileId);
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
    game.getPlayerByIdForManipulation(secondPlayerId).setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), waterUtilsTileId);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 70);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrentBalance(), startingBalance + 70);
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
    game.enableTilesBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), closestRailway);
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
    game.enableTilesBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    const std::vector<uint8_t> ownedTilesIds{closestRailway};
    EXPECT_EQ(player.getCurrTileId(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 200);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(closestRailway).getOwnerId(), firstPlayerId);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
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
    player2.addOwnedTileId(closestRailway);
    game.getBoardDataForModification().getTilesForModification().at(closestRailway).setOwnerId(secondPlayerId);
    game.getPlayersDataForManipulation().push_back(player2);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 50);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrentBalance(), startingBalance + 50);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
}

TEST_F(TestChance, TestGoToTile5FromTile6AndPlayerPaysAnotherPlayerWhoHasThreeRailroadTileCardId4)
{
    currentlyTestedCard = 4;

    const uint8_t closestRailway = 5;
    const uint8_t tileClosestToRailroad5Tile = 6;
    player.setCurrTile(tileClosestToRailroad5Tile);
    player.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);

    Player player2(secondPlayerId);
    player2.addOwnedTileId(closestRailway);
    player2.addOwnedTileId(15);
    player2.addOwnedTileId(25);
    game.getBoardDataForModification().getTilesForModification().at(closestRailway).setOwnerId(secondPlayerId);
    game.getBoardDataForModification().getTilesForModification().at(15).setOwnerId(secondPlayerId);
    game.getBoardDataForModification().getTilesForModification().at(25).setOwnerId(secondPlayerId);
    game.getPlayersDataForManipulation().push_back(player2);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 200);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
}

TEST_F(TestChance, TestGoToTile35FromTile32AndPlayerPaysAnotherPlayerWhoHasFourRailroadTileCardId4)
{
    currentlyTestedCard = 4;

    const uint8_t closestRailway = 35;
    const uint8_t tileClosestToRailroad5Tile = 32;
    player.setCurrTile(tileClosestToRailroad5Tile);
    player.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);

    Player player2(secondPlayerId);
    player2.addOwnedTileId(closestRailway);
    player2.addOwnedTileId(5);
    player2.addOwnedTileId(15);
    player2.addOwnedTileId(25);
    game.getBoardDataForModification().getTilesForModification().at(closestRailway).setOwnerId(secondPlayerId);
    game.getBoardDataForModification().getTilesForModification().at(5).setOwnerId(secondPlayerId);
    game.getBoardDataForModification().getTilesForModification().at(15).setOwnerId(secondPlayerId);
    game.getBoardDataForModification().getTilesForModification().at(25).setOwnerId(secondPlayerId);
    game.getPlayersDataForManipulation().push_back(player2);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 400);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrentBalance(), startingBalance + 400);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
}

TEST_F(TestChance, TestGoToTile17FromTile15AndPlayerBuysThatTileCardId4)
{
    currentlyTestedCard = 4;

    const uint8_t closestRailway = 15;
    const uint8_t tileClosestToRailroad5Tile = 17;
    player.setCurrTile(tileClosestToRailroad5Tile);
    player.setBalance(startingBalance);
    game.enableTilesBuying();

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    const std::vector<uint8_t> ownedTilesIds{closestRailway};
    EXPECT_EQ(player.getCurrTileId(), closestRailway);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 200);
    EXPECT_EQ(player.getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(closestRailway).getOwnerId(), firstPlayerId);
    EXPECT_EQ(player.hasInterActedWithTile(), true);
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

    EXPECT_EQ(player.hasGetOutOfPrisonChanceCard(), true);
}

TEST_F(TestChance, TestGoBack3TilesCardId7)
{
    currentlyTestedCard = 7;
    const uint8_t randomChanceTile = 7;
    player.setCurrTile(randomChanceTile);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), 7 - 3);
}

TEST_F(TestChance, TestGoToJailCardCardId8)
{
    currentlyTestedCard = 8;
    const uint8_t randomTile = 7;
    player.setCurrTile(randomTile);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), 10);
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
    EXPECT_EQ(player.getCurrTileId(), 5);
}

TEST_F(TestChance, TestGoToTile11AndNotPassStartCardId10)
{
    currentlyTestedCard = 10;
    const uint8_t randomNotStartTileBefore5 = 4;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore5);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTileId(), 5);
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

    EXPECT_EQ(player.getCurrTileId(), 39);
}

TEST_F(TestChance, TestPayEveryPlayer50CardId13)
{
    currentlyTestedCard = 13;
    Player player2(secondPlayerId);
    Player player3(thirdPlayerId);
    player.setBalance(startingBalance);
    player2.setBalance(startingBalance);
    player3.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);
    game.getPlayersDataForManipulation().push_back(player2);
    game.getPlayersDataForManipulation().push_back(player3);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 2 * 50);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrentBalance(), startingBalance + 50);
    EXPECT_EQ(game.getPlayerById(thirdPlayerId).getCurrentBalance(), startingBalance + 50);
}

TEST_F(TestChance, TestGet150CardId14)
{
    currentlyTestedCard = 14;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 150);
}

TEST_F(TestChance, playFirstThreeCardsOnOnePlayerCardIds0And1And2)
{
    player.setBalance(startingBalance);
    player.setCurrTile(6);

    chance.playNextCard(game, player, &mockDiceThrower);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTileId(), 0);

    player.setCurrTile(6);
    chance.playNextCard(game, player, &mockDiceThrower);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTileId(), 24);

    player.setCurrTile(22);
    chance.playNextCard(game, player, &mockDiceThrower);
    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200 + 200);
    EXPECT_EQ(player.getCurrTileId(), 11);
}

TEST_F(TestChance, tryToPlayCardId6ButGetOutOfPrisonCardIsNotAvailableSoCardId7IsUsed)
{
    player.setBalance(startingBalance);
    player.setCurrTile(7);

    chance.setNextCardIdToBePlayed(6);
    chance.setIsGetOutOfPrisonCardAvailable(false);
    chance.playNextCard(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTileId(), 7 - 3);
    EXPECT_EQ(chance.getNextCardIdToBePlayed(), 8);
}

} // namespace ut
