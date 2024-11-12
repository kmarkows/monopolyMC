#pragma once

#include <cstdlib>
#include <ctime>

#include "DiceResult.hpp"

class DiceThrower
{
  public:
    virtual DiceResult throwDice() const
    {
        DiceResult diceResult(getRandNumberFrom1To6(), getRandNumberFrom1To6());
        return diceResult;
    }

    virtual ~DiceThrower() = default;

  private:
    uint8_t getRandNumberFrom1To6() const
    {
        return 1 + (std::rand() % 6);
    }
};
