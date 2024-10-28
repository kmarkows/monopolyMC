#include "Trader.hpp"

#include "Logger.hpp"
#include "Utils.hpp"

void Trader::trade(Player &buyer, std::vector<Player> &players, Board &board, Utils &utils) const
{
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                  "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logTryTilesTrading(buyer);
    const std::array<std::vector<uint8_t>, 5> tileIdsToBuyToMissingTilesNum{
        createTileIdsToBuyToMissingTilesNum(buyer, board, utils)};
    std::stack<uint8_t> tileIdsToBuy{createTileIdsToBuy(buyer, board, tileIdsToBuyToMissingTilesNum, utils)};

    while (not tileIdsToBuy.empty())
    {
        const uint8_t tileIdBuyerWants = tileIdsToBuy.top();
        const auto &tileBuyerWants = board.getTiles().at(tileIdBuyerWants);
        const uint8_t potentialSellerId = tileBuyerWants.getOwnerId();
        if (potentialSellerId != invalidPlayerId)
        {
            const auto &potentiaSeller = utils.getPlayerById(players, potentialSellerId);
            const float sellingPrice = calcSellingPrice(potentiaSeller, tileBuyerWants, utils, tileIdBuyerWants);
            const float buyingPrice = calcBuyingPrice(buyer, tileBuyerWants, utils, tileIdBuyerWants);

            if ((buyer.getTradingStrategy().moneyToSpentAtTilesTrading * buyer.getCurrentBalance()) > buyingPrice and
                buyingPrice >= sellingPrice)
            {
                const int negotiatedPrice = static_cast<int>((buyingPrice + sellingPrice) / 2);
                auto &seller = utils.getPlayerByIdForManipulation(players, potentialSellerId);
                tradeTile(buyer, seller, board, tileIdBuyerWants, negotiatedPrice);
            }
        }
        tileIdsToBuy.pop();
    }
}

std::array<std::vector<uint8_t>, 5> Trader::createTileIdsToBuyToMissingTilesNum(Player &buyer, Board &board,
                                                                                Utils &utils) const
{
    std::array<std::vector<uint8_t>, 5> tileIdsToBuyToMissingTilesNum{};
    const auto &buyerTileIds = buyer.getOwnedTilesIds();
    for (const uint8_t buyerTileId : buyerTileIds)
    {
        const auto &buyerTile = board.getTiles().at(buyerTileId);
        const uint8_t numOfTilesOfGivenTypeMissingByBuyer =
            utils.getNumOfTilesOfGivenTypeMissingByPlayer(buyer, buyerTile);
        tileIdsToBuyToMissingTilesNum.at(numOfTilesOfGivenTypeMissingByBuyer).push_back(buyerTileId);
    }
    return tileIdsToBuyToMissingTilesNum;
}

std::stack<uint8_t> Trader::createTileIdsToBuy(const Player &buyer, const Board &board,
                                               const std::array<std::vector<uint8_t>, 5> &tileIdsToBuyToMissingTilesNum,
                                               const Utils &utils) const
{
    std::stack<uint8_t> tileIdsToBuy{};
    for (uint8_t i = 1; i < tileIdsToBuyToMissingTilesNum.size(); i++)
    {
        const auto &buyerTileIds = tileIdsToBuyToMissingTilesNum.at(i);
        for (int8_t j = buyerTileIds.size() - 1; j >= 0; j--)
        {
            const auto &buyerMissingTileIds =
                utils.getTileIdsOfGivenTypeMissingByPlayer(buyer, board.getTiles().at(buyerTileIds.at(j)));
            for (int8_t k = buyerMissingTileIds.size() - 1; k >= 0; k--)
            {
                if (tileIdsToBuy.empty())
                {
                    tileIdsToBuy.push(buyerMissingTileIds.at(k));
                }
                else
                {
                    if (tileIdsToBuy.top() != buyerMissingTileIds.at(k))
                    {
                        tileIdsToBuy.push(buyerMissingTileIds.at(k));
                    }
                }
            }
        }
    }
    return tileIdsToBuy;
}

const float Trader::calcSellingPrice(const Player &seller, const Tile &tile, const Utils &utils,
                                     const uint8_t tileId) const
{
    const auto &sellingStrategy = seller.getTradingStrategy();
    const float sellingFactor = sellingStrategy.sellingFactor;
    const float tileIdRatio = static_cast<float>(tileId) / static_cast<float>(numOfMonopolyBoradTiles);
    const float colorPrioFactor = 1.0f + (sellingStrategy.colorPriority == 0 ? (1.0f - tileIdRatio) : (tileIdRatio));
    const float numOfTilesOfEachTypeOwnedBySeller =
        static_cast<float>(utils.getNumOfTilesOfEachTypeOwnedByPlayer(seller, tile));
    const float sellingPrice = sellingFactor * colorPrioFactor * numOfTilesOfEachTypeOwnedBySeller * tile.getCost();
    return sellingPrice;
}

const float Trader::calcBuyingPrice(const Player &buyer, const Tile &tile, const Utils &utils,
                                    const uint8_t tileId) const
{
    const auto &buyingStrategy = buyer.getTradingStrategy();
    const float buyingFactor = buyingStrategy.buyingFactor;
    const float tileIdRatio = static_cast<float>(tileId) / static_cast<float>(numOfMonopolyBoradTiles);
    const float colorPrioFactor = 1.0f + (buyingStrategy.colorPriority == 0 ? (1.0f - tileIdRatio) : (tileIdRatio));
    const float numOfTilesOfEachTypeOwnedByBuyer =
        static_cast<float>(utils.getNumOfTilesOfEachTypeOwnedByPlayer(buyer, tile));
    const float buyingPrice = buyingFactor * colorPrioFactor * numOfTilesOfEachTypeOwnedByBuyer * tile.getCost();
    return buyingPrice;
}

void Trader::tradeTile(Player &buyer, Player &seller, Board &board, const uint8_t tileId, const int price) const
{
    buyer.addOwnedTileId(tileId);
    buyer.subtractBalance(price);
    seller.removeOwnedTileId(tileId);
    seller.addBalance(price);
    board.getTilesForModification().at(tileId).setOwnerId(buyer.getId());
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody "
                  "Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logTilesTrading(buyer, seller, board.getTiles().at(tileId), price);
}
