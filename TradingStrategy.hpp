#pragma once

struct TradingStrategy
{
    uint8_t colorPriority{0}; // 0 - 1, starting from cheapest - starting from most expensive
    float buyingFactor{1.0f};
    float sellingFactor{1.0f};
    float moneyToSpentAtTilesTrading{0.5f}; // factor of whole player balance
};
