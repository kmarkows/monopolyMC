#pragma once

#include "Board.hpp"
#include "DiceThrower.hpp"
#include "Player.hpp"

constexpr int prisonFine = 50;

class GetOutOfPrisonHandler
{
  public:
	GetOutOfPrisonHandler(Player &givenPlayer, const DiceThrower *givenDiceThrower);
	void handle();

  private:
	void moveAfterLeavingPrison(const DiceResult &diceResult);

	Player &player;
	const DiceThrower *diceThrower;
};
