#include "../../DiceResult.hpp"

template <uint8_t firstValue, uint8_t secondValue> class MockDiceThrower : public DiceThrower
{
    DiceResult throwDice() const override
    {
        DiceResult diceResult(firstValue, secondValue);
        return diceResult;
    }
};
