#pragma once

#include "DiceResult.hpp"

class DiceThrower
{
  public:
	virtual DiceResult throwDice() const
	{
		DiceResult diceResult(getRandNumberFrom1To6(), getRandNumberFrom1To6());
		return diceResult;
	}

  private:
	uint8_t getRandNumberFrom1To6() const
	{
		return 1 + (rand() % 6);
	}
};
