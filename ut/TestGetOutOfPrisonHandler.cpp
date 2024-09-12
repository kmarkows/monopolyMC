#include "../GetOutOfPrisonHandler.cpp"
#include "./mocks/MockDiceThrower.hpp"
#include <gtest/gtest.h>

namespace ut {

constexpr uint8_t firstPlayerId = 1;

class TestGetOutOfPrisonHandler : public ::testing::Test {
protected:
  Player player{firstPlayerId};
};

TEST_F(TestGetOutOfPrisonHandler, TestHaveGetOutOfPrisonCardStrategy1) {
  MockDiceThrower<1, 2> mockDiceThrower;
  player.acquireGetOutOfPrisonCard();
  player.goToPrison();
  player.setCurrTile(prisonTile);
  player.setStayingInPrisonStrategy(1);

  GetOutOfPrisonHandler getOutOfPrisonHandler(player, &mockDiceThrower);
  getOutOfPrisonHandler.handle();

  EXPECT_EQ(player.isInPrison(), false);
  EXPECT_EQ(player.getCurrTile(), prisonTile + 3);
}

TEST_F(TestGetOutOfPrisonHandler, TestHaveGetOutOfPrisonCardStrategy2) {
  MockDiceThrower<1, 2> mockDiceThrower;
  player.acquireGetOutOfPrisonCard();
  player.goToPrison();
  player.setCurrTile(prisonTile);
  player.setStayingInPrisonStrategy(2);

  GetOutOfPrisonHandler getOutOfPrisonHandler(player, &mockDiceThrower);
  getOutOfPrisonHandler.handle();

  EXPECT_EQ(player.isInPrison(), true);
  EXPECT_EQ(player.getCurrTile(), prisonTile);
}

TEST_F(TestGetOutOfPrisonHandler,
       TestDoesntHaveGetOutOfPrisonCardPays50Strategy0) {
  MockDiceThrower<1, 2> mockDiceThrower;
  player.goToPrison();
  player.setCurrTile(prisonTile);
  player.setStayingInPrisonStrategy(0);

  GetOutOfPrisonHandler getOutOfPrisonHandler(player, &mockDiceThrower);
  getOutOfPrisonHandler.handle();

  EXPECT_EQ(player.isInPrison(), false);
  EXPECT_EQ(player.getCurrTile(), prisonTile + 3);
  EXPECT_EQ(player.getCurrentBalance(), startingBalance - prisonFine);
}

TEST_F(TestGetOutOfPrisonHandler, TestThrowDoubleStrategy2) {
  MockDiceThrower<2, 2> mockDiceThrower;
  player.goToPrison();
  player.setCurrTile(prisonTile);
  player.setStayingInPrisonStrategy(2);

  GetOutOfPrisonHandler getOutOfPrisonHandler(player, &mockDiceThrower);
  getOutOfPrisonHandler.handle();

  EXPECT_EQ(player.isInPrison(), false);
  EXPECT_EQ(player.getCurrTile(), prisonTile + 4);
}

TEST_F(TestGetOutOfPrisonHandler, TestNotThrowDoubleForFirstTimeStrategy2) {
  MockDiceThrower<2, 1> mockDiceThrower;
  player.goToPrison();
  player.setCurrTile(prisonTile);
  player.setStayingInPrisonStrategy(2);

  GetOutOfPrisonHandler getOutOfPrisonHandler(player, &mockDiceThrower);
  getOutOfPrisonHandler.handle();

  EXPECT_EQ(player.isInPrison(), true);
  EXPECT_EQ(player.getCurrTile(), prisonTile);
}

TEST_F(TestGetOutOfPrisonHandler, TestNotThrowDoubleForThirdTimeStrategy2) {
  MockDiceThrower<2, 1> mockDiceThrower;
  player.goToPrison();
  player.setCurrTile(prisonTile);
  player.incrementTurnsSpentInPrison();
  player.incrementTurnsSpentInPrison();
  player.setStayingInPrisonStrategy(2);

  GetOutOfPrisonHandler getOutOfPrisonHandler(player, &mockDiceThrower);
  getOutOfPrisonHandler.handle();

  EXPECT_EQ(player.isInPrison(), false);
  EXPECT_EQ(player.getCurrTile(), prisonTile + 3);
  EXPECT_EQ(player.getCurrentBalance(), startingBalance - prisonFine);
}

} // namespace ut