#pragma once

#include <cstdlib>

class DiceThrowerSingle
{
  public:
	virtual uint8_t throwDice() const
	{
		return getRandNumberFrom1To6();
	}

  private:
	uint8_t getRandNumberFrom1To6() const
	{
		return 1 + (rand() % 6);
	}
};
