#include "../Game.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include <gtest/gtest.h>

namespace ut
{

constexpr uint8_t firstPlayerId = 1;
constexpr uint8_t secondPlayerId = 2;
constexpr int startingBalance = 1500;

class TestGame : public ::testing::Test
{
  protected:
    uint32_t iterations;
    uint32_t numOfPlayers;
    std::vector<uint8_t> defaultPlayerOrder{1, 2, 3, 4, 5, 6, 7, 8};
};

TEST_F(TestGame, testMovement)
{
    iterations = 5;
    numOfPlayers = 1;
    MockDiceThrower<1, 2> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    game.play();

    const uint8_t finishTile = 15;
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), finishTile);
    EXPECT_EQ(game.getPlayersData().at(0).getPreviousDiceRollSum(), 3);
}

TEST_F(TestGame, TestGoToPrison)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<6, 6> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), true);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), prisonTile);
}

TEST_F(TestGame, TestGetOutOfPrisonThrowingDouble)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<6, 6> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    constexpr uint8_t likesToStayInPrison = 2;
    game.getPlayersDataForManipulation().at(0).goToPrison();
    game.getPlayersDataForManipulation().at(0).setCurrTile(prisonTile);
    game.getPlayersDataForManipulation().at(0).setStayingInPrisonStrategy(likesToStayInPrison);

    game.play();

    const uint8_t finishTile = prisonTile + 12;
    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), false);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), finishTile);
}

TEST_F(TestGame, TestGetOutOfPrisonNotThrowingDouble)
{
    iterations = 3;
    numOfPlayers = 1;
    MockDiceThrower<1, 2> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    constexpr uint8_t likesToStayInPrison = 2;
    game.getPlayersDataForManipulation().at(0).goToPrison();
    game.getPlayersDataForManipulation().at(0).setCurrTile(prisonTile);
    game.getPlayersDataForManipulation().at(0).setStayingInPrisonStrategy(likesToStayInPrison);

    game.play();

    const uint8_t finishTile = prisonTile + 3;
    EXPECT_EQ(game.getPlayersData().at(0).isInPrison(), false);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), finishTile);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), startingBalance - prisonFine);
}

TEST_F(TestGame, TestGoingThroughStartTileAndGet200)
{
    iterations = 7;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1700);
}

TEST_F(TestGame, TestGoOnIncomeTaxAndPay)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1300);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), 4);
}

TEST_F(TestGame, TestGoOnLuxuryTaxAndPay)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    game.getPlayersDataForManipulation().at(0).setCurrTile(31);

    game.play();

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(), 1400);
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), 38);
}

TEST_F(TestGame, TestGoOnIncomeTaxPayAndLoseGame)
{
    iterations = 1;
    numOfPlayers = 2;
    MockDiceThrower<3, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);

    game.getPlayerByIdForManipulation(firstPlayerId).setBalance(200);

    game.play();

    EXPECT_EQ(game.getPlayersData().size(), 1);
}

TEST_F(TestGame, TestGoOn3rdTileAndBuyProperty)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<2, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.enableTilesBuying();

    game.play();

    const uint8_t tileToBuy = 3;
    const uint8_t buyerId = 1;

    const std::vector<uint8_t> ownedTilesIds{tileToBuy};
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), tileToBuy);
    EXPECT_EQ(game.getPlayersData().at(0).getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);
}

TEST_F(TestGame, TestGoOn5rdTileAndBuyRailroad)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<2, 3> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.enableTilesBuying();

    game.play();

    const uint8_t tileToBuy = 5;
    const uint8_t buyerId = 1;

    const std::vector<uint8_t> ownedTilesIds{tileToBuy};
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), tileToBuy);
    EXPECT_EQ(game.getPlayersData().at(0).getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);
}

TEST_F(TestGame, TestGoOn5rdTileAndBuyPropertyAndUtilities)
{
    iterations = 2;
    numOfPlayers = 1;
    MockDiceThrower<4, 2> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.enableTilesBuying();

    game.play();

    const uint8_t tile1ToBuy = 6;
    const uint8_t tile2ToBuy = 12;
    const uint8_t buyerId = 1;

    const std::vector<uint8_t> ownedTilesIds{tile1ToBuy, tile2ToBuy};
    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tile1ToBuy).getCost() -
                  game.getBoardData().getTiles().at(tile2ToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), tile2ToBuy);
    EXPECT_EQ(game.getPlayersData().at(0).getOwnedTilesIds(), ownedTilesIds);
    EXPECT_EQ(game.getBoardData().getTiles().at(tile1ToBuy).getOwnerId(), buyerId);
    EXPECT_EQ(game.getBoardData().getTiles().at(tile2ToBuy).getOwnerId(), buyerId);
}

TEST_F(TestGame, TestPlayer1Buys3rdPropertyAndLaterPlayer2CannotBuyIt)
{
    iterations = 1;
    numOfPlayers = 2;
    MockDiceThrower<2, 1> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.enableTilesBuying();

    game.play();

    const uint8_t tileToBuy = 3;
    const uint8_t buyerId = 1;

    EXPECT_EQ(game.getPlayersData().at(0).getCurrentBalance(),
              startingBalance - game.getBoardData().getTiles().at(tileToBuy).getCost());
    EXPECT_EQ(game.getPlayersData().at(0).getCurrTileId(), tileToBuy);
    EXPECT_EQ(game.getBoardData().getTiles().at(tileToBuy).getOwnerId(), buyerId);

    EXPECT_EQ(game.getPlayersData().at(1).getCurrentBalance(), startingBalance);
    EXPECT_EQ(game.getPlayersData().at(1).getCurrTileId(), tileToBuy);
}

TEST_F(TestGame, TestPlayerGoesToChanceTileId7)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.enableTilesBuying();
    game.enableCards();
    game.getChanceForModification().setNextCardIdToBePlayed(0);

    game.play();

    EXPECT_EQ(game.getPlayerById(firstPlayerId).getCurrTileId(), 0);
    EXPECT_EQ(game.getPlayerById(firstPlayerId).getCurrentBalance(), startingBalance + 200);
}

TEST_F(TestGame, TestPlayerStartsOnPrisonTileRolls7AndGoesToCommunityChestTileId17)
{
    iterations = 1;
    numOfPlayers = 1;
    MockDiceThrower<3, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.getPlayerByIdForManipulation(firstPlayerId).setCurrTile(prisonTile);
    game.enableTilesBuying();
    game.enableCards();
    game.getCommunityChestForModification().setNextCardIdToBePlayed(0);
    game.enablePaying();

    game.play();

    EXPECT_EQ(game.getPlayerById(firstPlayerId).getCurrTileId(), 0);
    EXPECT_EQ(game.getPlayerById(firstPlayerId).getCurrentBalance(), startingBalance + 200);
}

TEST_F(TestGame, TestFirstPlayerGoesToTileId6BuysIdAndThenSecondPlayerGoesToThatTileAndPaysrentNoHouses)
{
    iterations = 1;
    numOfPlayers = 2;
    MockDiceThrower<2, 4> mockDiceThrower;

    Game game(iterations, numOfPlayers, &mockDiceThrower, defaultPlayerOrder);
    game.enableTilesBuying();
    game.enablePaying();

    game.play();

    EXPECT_EQ(game.getPlayerById(firstPlayerId).getCurrTileId(), 6);
    EXPECT_EQ(game.getPlayerById(firstPlayerId).getCurrentBalance(), startingBalance + 6 - 100);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrTileId(), 6);
    EXPECT_EQ(game.getPlayerById(secondPlayerId).getCurrentBalance(), startingBalance - 6);
}

} // namespace ut
