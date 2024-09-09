#include "../Chance.cpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;

class TestChance : public ::testing::Test
{
protected:
    Player player{firstPlayerId};
    Board board;
    Chance chance;
    uint8_t currentlyTestedCard;
};

TEST_F(TestChance, TestGoToStartFieldCardId0)
{
    currentlyTestedCard = 0;
    const uint8_t randomNotStartTile = 15;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTile);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 0);
}

TEST_F(TestChance, TestGoToTile24AndPassStartCardId1)
{
    currentlyTestedCard = 1;
    const uint8_t randomNotStartTileAfter24 = 27;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter24);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 24);
}

TEST_F(TestChance, TestGoToTile24AndNotPassStartCardId1)
{
    currentlyTestedCard = 1;
    const uint8_t randomNotStartTileBefore24 = 21;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore24);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTile(), 24);
}

TEST_F(TestChance, TestGoToTile11AndPassStartCardId2)
{
    currentlyTestedCard = 2;
    const uint8_t randomNotStartTileAfter11 = 20;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter11);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 11);
}

TEST_F(TestChance, TestGoToTile11AndNotPassStartCardId2)
{
    currentlyTestedCard = 2;
    const uint8_t randomNotStartTileBefore11 = 9;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore11);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTile(), 11);
}

TEST_F(TestChance, TestGetDividend50CardId5)
{
    currentlyTestedCard = 5;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 50);
}

TEST_F(TestChance, TestAcquireGetOutOfPrisonCardCardId6)
{
    currentlyTestedCard = 6;

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.hasGetOutOfPrisonCard(), true);
}

TEST_F(TestChance, TestGoToJailCardCardId8)
{
    currentlyTestedCard = 8;
    const uint8_t randomTile = 7;
    player.setCurrTile(randomTile);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrTile(), 10);
    EXPECT_EQ(player.isInPrison(), true);
}

TEST_F(TestChance, TestGoToTile5AndPassStartCardId10)
{
    currentlyTestedCard = 10;
    const uint8_t randomNotStartTileAfter5 = 6;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileAfter5);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 200);
    EXPECT_EQ(player.getCurrTile(), 5);
}

TEST_F(TestChance, TestGoToTile11AndNotPassStartCardId10)
{
    currentlyTestedCard = 10;
    const uint8_t randomNotStartTileBefore5 = 4;
    player.setBalance(startingBalance);
    player.setCurrTile(randomNotStartTileBefore5);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance);
    EXPECT_EQ(player.getCurrTile(), 5);
}

TEST_F(TestChance, TestPayPoorTax15CardId11)
{
    currentlyTestedCard = 11;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance - 15);
}

TEST_F(TestChance, TestAdvanceToTile39CardId12)
{
    currentlyTestedCard = 12;
    const uint8_t randomTile = 6;
    player.setCurrTile(randomTile);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrTile(), 39);
}

TEST_F(TestChance, TestGet150CardId14)
{
    currentlyTestedCard = 14;
    player.setBalance(startingBalance);

    chance.getCardById(currentlyTestedCard).doAction(player, board);

    EXPECT_EQ(player.getCurrentBalance(), startingBalance + 150);
}

} // namespace ut
