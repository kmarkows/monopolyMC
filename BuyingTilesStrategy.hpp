#pragma once

struct BuyingTilesStrategy
{
    float firstHalfPropertiesFactor{1.0f};  // the bigger the harder to buy that tile always > 1.0
    float secondHalfPropertiesFactor{1.0f}; // the bigger the harder to buy that tile always > 1.0
    float moneyToSpentAtTilesBuying{0.5f};  // factor of whole player balance
};