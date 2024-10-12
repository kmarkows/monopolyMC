#include "GetOutOfPrisonHandler.hpp"
#include "Logger.hpp"

GetOutOfPrisonHandler::GetOutOfPrisonHandler(Player &givenPlayer, const DiceThrower *givenDiceThrower)
    : player{givenPlayer}, diceThrower{givenDiceThrower} {};

void GetOutOfPrisonHandler::handle()
{
    Logger logger("/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
    logger.logPlayerTriesToGetOutOfPrison(player);
    if (player.hasGetOutOfPrisonCard() and
        (player.getStayingInPrisonStrategy() == 0 or player.getStayingInPrisonStrategy() == 1))
    {
        player.getOutOfPrison();
        player.useGetOutOfPrisonCard();
        const auto diceResult = diceThrower->throwDice();
        moveAfterLeavingPrison(diceResult);
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logPlayerGetsOutOfPrisonByCard(player);
        return;
    }

    if (player.getStayingInPrisonStrategy() == 0 and player.getCurrentBalance() > prisonFine)
    {
        player.getOutOfPrison();
        player.subtractBalance(prisonFine);
        const auto diceResult = diceThrower->throwDice();
        moveAfterLeavingPrison(diceResult);
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logPlayerGetsOutOfPrisonByFine(player);
        return;
    }

    const auto diceResult = diceThrower->throwDice();
    if (player.getTurnsSpentInPrison() == 2)
    {
        player.getOutOfPrison();
        player.subtractBalance(prisonFine);
        moveAfterLeavingPrison(diceResult);
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logPlayerGetsOutOfPrisonByStaying(player);
        return;
    }
    // std::cout << (int)diceResult.getFirst() << " " <<
    // (int)diceResult.getSecond() << std::endl; std::cout << "trying to get out
    // of prison" << std::endl;

    if (diceResult.getFirst() == diceResult.getSecond())
    {
        // std::cout << "got out of prison" << std::endl;
        player.getOutOfPrison();
        moveAfterLeavingPrison(diceResult);
        Logger logger(
            "/Users/konradmarkowski/Documents/Projekty Metody Numeryczne/MonopolyMc/logs/monopolyGameLogs.txt");
        logger.logPlayerGetsOutOfPrisonByDouble(player, diceResult);
    }
    else
    {
        // std::cout << "increment get out of prison counter" << std::endl;
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