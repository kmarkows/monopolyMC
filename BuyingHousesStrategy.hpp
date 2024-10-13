#pragma once

#include <cstdint>

// TO DO add not to buy hotels
struct BuyingHousesStrategy
{
    uint8_t colorPriority{0};              // 0 - 1, atarting from cheapest - starting from most expensive
    float moneyToSpentAtHouseBuying{0.5f}; // factor of whole player balance
    bool isBuyingHotels{true};
};