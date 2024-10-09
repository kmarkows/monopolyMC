#pragma once

#include <cstdint>

struct BuyingHousesStrategy
{
    uint8_t colorPriority{0};              // 0 - 1, atarting from cheapest - starting from most expensive
    float moneyToSpentAtHouseBuying{0.5f}; // factor of whole player balance
};