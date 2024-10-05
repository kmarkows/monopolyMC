#pragma once

struct BuyingHousesStrategy
{
    uint8_t colorPriority{0};              // 0 - 1, atarting from cheapest - starting from most expensive
    float moneyToSpentAtHouseBuying{0.0f}; // factor of whole player balance
};