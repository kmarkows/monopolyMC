#include "../Game.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include "./mocks/MockDiceThrowerSingle.hpp"
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
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

    game.play();

    const uint8_t finishTile = 15;
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), finishTile);
}

TEST_F(TestGame, TestGoToPrison)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<6, 6> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), true);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), prisonTile);
}

TEST_F(TestGame, TestGetOutOfPrisonThrowingDouble)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<6, 6> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

    constexpr uint8_t likesToStayInPrison = 2;
    game.getPlayersDataForManipulation().at(0).goToPrison();
    game.getPlayersDataForManipulation().at(0).setCurrTile(prisonTile);
    game.getPlayersDataForManipulation().at(0).setStayingInPrisonStrategy(likesToStayInPrison);

    game.play();

    const uint8_t finishTile = prisonTile + 12;
    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), false);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), finishTile);
}

TEST_F(TestGame, TestGetOutOfPrisonNotThrowingDouble)
{
    iterations = 3;
    numOfPlayers = 1;
    MockDiceThrower<1, 2> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

    constexpr uint8_t likesToStayInPrison = 2;
    game.getPlayersDataForManipulation().at(0).goToPrison();
    game.getPlayersDataForManipulation().at(0).setCurrTile(prisonTile);
    game.getPlayersDataForManipulation().at(0).setStayingInPrisonStrategy(likesToStayInPrison);

    game.play();

    const uint8_t finishTile = prisonTile + 3;
    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), false);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), finishTile);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), startingBalance - prisonFine);
}

TEST_F(TestGame, TestGoingThroughStartTileAndGet200)
{
    iterations = 7;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1700);
}

TEST_F(TestGame, TestGoOnIncomeTaxAndPay)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 1> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1300);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), 4);
}

TEST_F(TestGame, TestGoOnLuxuryTaxAndPay)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

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
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);

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
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);
    game.enableBuying();

    game.play();

    const uint8_t tileToBuy = 3;
    const uint8_t buyerId = 1;

    const std::vector<uint8_t> ownedTilesIds{tileToBuy};
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), tileToBuy);
    EXPECT_EQ(game.getPlayersData().at(0).getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);
}

TEST_F(TestGame, TestGoOn5rdTileAndBuyRailroad)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<2, 3> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);
    game.enableBuying();

    game.play();

    const uint8_t tileToBuy = 5;
    const uint8_t buyerId = 1;

    const std::vector<uint8_t> ownedTilesIds{tileToBuy};
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), tileToBuy);
    EXPECT_EQ(game.getPlayersData().at(0).getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);
}

TEST_F(TestGame, TestGoOn5rdTileAndBuyPropertyAndUtilities)
{
    iterations = 2;
    numOfPlayers = 1;
    MockDiceThrower<4, 2> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);
    game.enableBuying();

    game.play();

    const uint8_t tile1ToBuy = 6;
    const uint8_t tile2ToBuy = 12;
    const uint8_t buyerId = 1;

    const std::vector<uint8_t> ownedTilesIds{tile1ToBuy, tile2ToBuy};
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tile1ToBuy).getCost() -
                  game.getBoardData().getTiles().at(tile2ToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), tile2ToBuy);
    EXPECT_EQ(game.getPlayersData().at(0).getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(tile1ToBuy).getOwnerId(), buyerId);
    EXPECT_EQ(game.getBoardData().getTiles().at(tile2ToBuy).getOwnerId(), buyerId);
}

TEST_F(TestGame, TestPlayer1Buys3rdPropertyAndLaterPlayer2CannotBuyIt)
{
    iterations = 1;
    numOfPlayers = 2;
    MockDiceThrower<2, 1> mockDiceThrower;
    MockDiceThrowerSingle<1> mockDiceThrowerSingle;

    Game game(iterations, numOfPlayers, &mockDiceThrower, &mockDiceThrowerSingle);
    game.enableBuying();

    game.play();

    const uint8_t tileToBuy = 3;
    const uint8_t buyerId = 1;

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTile(), tileToBuy);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);

    EXPECT_EQ(game.getPlayersData().at(1).getCurrentBalance(), startingBalance);
    EXPECT_EQ(game.getPlayersData().at(1).getCurrTile(), tileToBuy);
}

} // namespace ut
