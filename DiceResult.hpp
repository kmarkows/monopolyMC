#pragma once

#include <cinttypes>

class DiceResult
{
  public:
    DiceResult(const uint8_t num1, const uint8_t num2) : first(num1), second(num2){};
    uint8_t getFirst() const
    {
        return first;
    }
    uint8_t getSecond() const
    {
        return second;
    }
    DiceResult operator=(const DiceResult &diceResult)
    {
        if (this != &diceResult)
        {
            first = diceResult.first;
            second = diceResult.second;
        }
        return *this;
    }

  private:
    uint8_t first;
    uint8_t second;
};