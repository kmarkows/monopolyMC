#include "../Game.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include <gtest/gtest.h>

namespace ut
{

class TestGame : public ::testing::Test
{
protected:
    uint32_t iterations;
    uint32_t numOfPlayers;
};

TEST_F(TestGame, testMovement)
{
    iterations = 5;
    numOfPlayers = 1;
    MockDiceThrower<1, 2> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.play();

    const uint8_t finishTile = 15;
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), finishTile);
}

TEST_F(TestGame, TestGoToPrison)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<6, 6> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), true);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), prisonTile);
}

TEST_F(TestGame, TestGetOutOfPrisonThrowingDouble)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<6, 6> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.getPlayersDataForManipulation().at(0).goToPrison();
    game.getPlayersDataForManipulation().at(0).setCurrTile(prisonTile);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), false);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), prisonTile);
}

TEST_F(TestGame, TestGetOutOfPrisonNotThrowingDouble)
{
    iterations = 3;
    numOfPlayers = 1;
    MockDiceThrower<1, 2> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.getPlayersDataForManipulation().at(0).goToPrison();
    game.getPlayersDataForManipulation().at(0).setCurrTile(prisonTile);

    game.play();

    const uint8_t finishTile = prisonTile + 3;
    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), false);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), finishTile);
}

TEST_F(TestGame, TestGoingThroughStartTileAndGet200)
{
    iterations = 7;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1700);
}

TEST_F(TestGame, TestGoOnIncomeTaxAndPay)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1300);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), 4);
}

TEST_F(TestGame, TestGoOnLuxuryTaxAndPay)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.getPlayersDataForManipulation().at(0).setCurrTile(31);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1400);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), 38);
}

TEST_F(TestGame, TestGoOnIncomeTaxPayAndLoseGame)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);

    game.getPlayersDataForManipulation().at(0).setBalance(200);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 0);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), 4);
    EXPECT_EQ(game.getPlayersData().at(0).isPlaying(), false);
}

TEST_F(TestGame, TestGoOn3rdTileAndBuyProperty)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<2, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower);
    game.enableBuying();

    game.play();

    const uint8_t tileToBuy = 3;
    const uint8_t buyerId = 1;
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), tileToBuy);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);
}

} // namespace ut
