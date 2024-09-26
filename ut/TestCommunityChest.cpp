#include "../CommunityChest.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;

class TestCommunityChest : public ::testing::Test
{
  protected:
    Player player{firstPlayerId};
    Game game;
    CommunityChest communityChest;
    MockDiceThrower<4, 3> mockDiceThrower;
    uint8_t currentlyTestedCard;
};

TEST_F(TestCommunityChest, TestGoToStartFieldCardId0)
{
    currentlyTestedCard = 0;
    const uint8_t randomNotStartTile = 15;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTile);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 0);
}

TEST_F(TestCommunityChest, TestBankErrorGet200CardId1)
{
    currentlyTestedCard = 1;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
}

TEST_F(TestCommunityChest, TestVisitDoctorPay50CardId2)
{
    currentlyTestedCard = 2;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 50);
}

TEST_F(TestCommunityChest, TestSellStockGet50CardId3)
{
    currentlyTestedCard = 3;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 50);
}

TEST_F(TestCommunityChest, TestGetOutOfPrisonCardCardId4)
{
    currentlyTestedCard = 4;

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.hasGetOutOfPrisonCard(), true);
}

TEST_F(TestCommunityChest, TestGoToJailCardCardId5)
{
    currentlyTestedCard = 5;
    const uint8_t randomTile = 7;
    player.setCurrTile(randomTile);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrTile(), prisonTile);
    EXPECT_EQ(player.isInPrison(), true);
}

TEST_F(TestCommunityChest, TestCurrPlayerGets50FromEveryOtherId6)
{
    currentlyTestedCard = 6;
    Player player2(2);
    Player player3(3);
    player.setBalance(startingBalance);
    player2.setBalance(startingBalance);
    player3.setBalance(startingBalance);
    game.getPlayersDataForManipulation().push_back(player);
    game.getPlayersDataForManipulation().push_back(player2);
    game.getPlayersDataForManipulation().push_back(player3);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 2 * 50);
    EXPECT_EQ(game.getPlayersData().at(1).getCurrentBalance(), startingBalance - 50);
    EXPECT_EQ(game.getPlayersData().at(2).getCurrentBalance(), startingBalance - 50);
}

TEST_F(TestCommunityChest, TestXmaxGiftGet100CardId7)
{
    currentlyTestedCard = 7;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 100);
}

TEST_F(TestCommunityChest, TestTaxRefundGet20CardId8)
{
    currentlyTestedCard = 8;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 20);
}

TEST_F(TestCommunityChest, TestYourBirthdayGet10CardId9)
{
    currentlyTestedCard = 9;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 10);
}

TEST_F(TestCommunityChest, TestLifeInsuranceMaturesGet100CardId10)
{
    currentlyTestedCard = 10;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 100);
}

TEST_F(TestCommunityChest, TestHospitalFeePay50CardId11)
{
    currentlyTestedCard = 11;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 50);
}

TEST_F(TestCommunityChest, TestSchoolFeePay50CardId12)
{
    currentlyTestedCard = 12;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 50);
}

TEST_F(TestCommunityChest, TestConsultancyFeePay50CardId13)
{
    currentlyTestedCard = 13;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 25);
}

TEST_F(TestCommunityChest, TestGeneralRepairsPay40ForEveryHouseAnd125ForHotelCardId14)
{
    currentlyTestedCard = 14;
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

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - (2 * 40 + 115));
}

TEST_F(TestCommunityChest, TestWinBeautyContestGet10CardId15)
{
    currentlyTestedCard = 15;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 10);
}

TEST_F(TestCommunityChest, TestInheritMoneyGet100CardId16)
{
    currentlyTestedCard = 16;
    player.setBalance(startingBalance);

    communityChest.getCardById(currentlyTestedCard).doAction(game, player, &mockDiceThrower);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 100);
}

} // namespace ut
