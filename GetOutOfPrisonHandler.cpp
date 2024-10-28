#include "GetOutOfPrisonHandler.hpp"
#include "Logger.hpp"

GetOutOfPrisonHandler::GetOutOfPrisonHandler(Player &givenPlayer, const DiceThrower *givenDiceThrower)
    : player{givenPlayer}, diceThrower{givenDiceThrower} {};

void GetOutOfPrisonHandler::handle()
{
    Logger logger;
    logger.logPlayerTriesToGetOutOfPrison(player);
    if (player.hasGetOutOfPrisonCard() and
        (player.getStayingInPrisonStrategy() == 0 or player.getStayingInPrisonStrategy() == 1))
    {
        player.getOutOfPrison();
        player.useGetOutOfPrisonCard();
        const auto diceResult = diceThrower->throwDice();
        moveAfterLeavingPrison(diceResult);
        Logger logger;
        logger.logPlayerGetsOutOfPrisonByCard(player, diceResult);
        return;
    }

    if (player.getStayingInPrisonStrategy() == 0 and player.getCurrentBalance() > prisonFine)
    {
        player.getOutOfPrison();
        player.subtractBalance(prisonFine);
        const auto diceResult = diceThrower->throwDice();
        moveAfterLeavingPrison(diceResult);
        Logger logger;
        logger.logPlayerGetsOutOfPrisonByFine(player, diceResult);
        return;
    }

    const auto diceResult = diceThrower->throwDice();
    if (player.getTurnsSpentInPrison() == 2)
    {
        player.getOutOfPrison();
        player.subtractBalance(prisonFine);
        moveAfterLeavingPrison(diceResult);
        Logger logger;
        logger.logPlayerGetsOutOfPrisonByStaying(player, diceResult);
        return;
    }

    if (diceResult.getFirst() == diceResult.getSecond())
    {
        player.getOutOfPrison();
        moveAfterLeavingPrison(diceResult);
        Logger logger;
        logger.logPlayerGetsOutOfPrisonByDouble(player, diceResult);
    }
    else
    {
        player.incrementTurnsSpentInPrison();
    }
}

void GetOutOfPrisonHandler::moveAfterLeavingPrison(const DiceResult &diceResult)
{
    auto nextTile = player.getCurrTileId();
    nextTile += (diceResult.getFirst() + diceResult.getSecond());
    nextTile = nextTile % numOfMonopolyBoradTiles;
    player.setCurrTile(nextTile);
}