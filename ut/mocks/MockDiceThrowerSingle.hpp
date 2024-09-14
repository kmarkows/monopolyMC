#include "../../DiceResult.hpp"

template <uint8_t value>
class MockDiceThrowerSingle : public DiceThrowerSingle {
  uint8_t throwDice() const override {
    return value;
  }
};
