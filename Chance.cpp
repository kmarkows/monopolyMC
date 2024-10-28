#include "Chance.hpp"
#include "DiceThrower.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Utils.hpp"

Chance::Chance()
{
    cards.at(0) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.setCurrTile(0);
            currPlayer.addBalance(200);
        },
        0);

    cards.at(1) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            if (currPlayer.getCurrTileId() > 24)
            {
                currPlayer.addBalance(200);
            }
            currPlayer.setCurrTile(24);
        },
        1);

    cards.at(2) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            if (currPlayer.getCurrTileId() > 11)
            {
                currPlayer.addBalance(200);
            }
            currPlayer.setCurrTile(11);
        },
        2);

    cards.at(3) = Card(
        [this](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.setInteractedWithTile();
            if (currPlayer.getCurrTileId() < 20)
            {
                const uint8_t firstUtilitiesTileId = 12;
                handleUtility(game, currPlayer, diceThrower, firstUtilitiesTileId);
            }
            else
            {
                const uint8_t secondUtilitiesTileId = 28;
                handleUtility(game, currPlayer, diceThrower, secondUtilitiesTileId);
            }
        },
        3);

    cards.at(4) = Card(
        [this](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.setInteractedWithTile();
            if (currPlayer.getCurrTileId() >= 0 and currPlayer.getCurrTileId() < 10)
            {
                const uint8_t nearestRailroadTileId = 5;
                handleRailroad(game, currPlayer, nearestRailroadTileId);
                return;
            }
            else if (currPlayer.getCurrTileId() >= 10 and currPlayer.getCurrTileId() < 20)
            {
                const uint8_t nearestRailroadTileId = 15;
                handleRailroad(game, currPlayer, nearestRailroadTileId);
                return;
            }
            else if (currPlayer.getCurrTileId() >= 20 and currPlayer.getCurrTileId() < 30)
            {
                const uint8_t nearestRailroadTileId = 25;
                handleRailroad(game, currPlayer, nearestRailroadTileId);
                return;
            }
            else
            {
                const uint8_t nearestRailroadTileId = 35;
                handleRailroad(game, currPlayer, nearestRailroadTileId);
                return;
            }
        },
        4);

    cards.at(5) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(50); }, 5);

    cards.at(6) = Card(
        [this](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.acquireGetOutOfPrisonChanceCard();
            isGetOutOfPrisonCardAvailable = false;
        },
        6);

    cards.at(7) = Card([](Game &game, Player &currPlayer,
                          const DiceThrower *diceThrower) { currPlayer.setCurrTile(currPlayer.getCurrTileId() - 3); },
                       7);

    cards.at(8) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.goToPrison();
            currPlayer.setCurrTile(prisonTile);
        },
        8);

    cards.at(9) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            uint8_t numOfHouses = 0;
            uint8_t numOfHotels = 0;
            for (const uint8_t ownedTilesIds : currPlayer.getOwnedTilesIds())
            {
                uint8_t numOfRealEstates = game.getBoardData().getTiles().at(ownedTilesIds).getNumOfHouses();
                if (numOfRealEstates == 5)
                {
                    numOfHotels++;
                }
                else
                {
                    numOfHouses += numOfRealEstates;
                }
            }
            int totalRepairCost = numOfHouses * 25 + numOfHotels * 100;
            currPlayer.subtractBalance(totalRepairCost);
        },
        9);

    cards.at(10) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            if (currPlayer.getCurrTileId() > 5)
            {
                currPlayer.addBalance(200);
            }
            currPlayer.setCurrTile(5);
        },
        10);

    cards.at(11) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.subtractBalance(15); }, 11);

    cards.at(12) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.setCurrTile(39); }, 12);

    cards.at(13) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            for (auto &player : game.getPlayersDataForManipulation())
            {
                if (player.getId() != currPlayer.getId())
                {
                    player.addBalance(50);
                    currPlayer.subtractBalance(50);
                }
            }
        },
        13);

    cards.at(14) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(150); }, 14);
}

void Chance::playNextCard(Game &game, Player &player, const DiceThrower *diceThrower)
{
    if (not isGetOutOfPrisonCardAvailable and nextCardIdToBePlayed == 6)
    {
        nextCardIdToBePlayed++;
    }
    Logger logger;
    logger.logDrawCardChance(player, nextCardIdToBePlayed);

    cards.at(nextCardIdToBePlayed).doAction(game, player, diceThrower);
    nextCardIdToBePlayed++;
    nextCardIdToBePlayed = nextCardIdToBePlayed % chanceCardsNumber;
}

void Chance::setNextCardIdToBePlayed(const uint8_t givenNextCardIdToBePlayed)
{
    nextCardIdToBePlayed = givenNextCardIdToBePlayed;
}

void Chance::setIsGetOutOfPrisonCardAvailable(const uint8_t givenIsGetOutOfPrisonCardAvailable)
{
    isGetOutOfPrisonCardAvailable = givenIsGetOutOfPrisonCardAvailable;
}

const Card &Chance::getCardById(const uint8_t id) const
{
    return cards.at(id);
}

const uint8_t Chance::getNextCardIdToBePlayed() const
{
    return nextCardIdToBePlayed;
}

const bool Chance::getIsGetOutOfPrisonCardAvailable() const
{
    return isGetOutOfPrisonCardAvailable;
}

void Chance::handleUtility(Game &game, Player &currPlayer, const DiceThrower *diceThrower,
                           const uint8_t utilityTileId) const
{
    currPlayer.setCurrTile(utilityTileId);
    auto &tile = game.getBoardDataForModification().getTilesForModification().at(utilityTileId);

    if (tile.getOwnerId() == currPlayer.getId())
    {
        return;
    }
    if (tile.getOwnerId() == invalidPlayerId)
    {
        if (currPlayer.getCurrentBalance() > tile.getCost() and game.isBuyingTilesEnabled())
        {
            tile.setOwnerId(currPlayer.getId());
            currPlayer.addOwnedTileId(tile.getId());
            currPlayer.subtractBalance(tile.getCost());
        }
        return;
    }

    const DiceResult diceResult = diceThrower->throwDice();
    const int diceResultSum = diceResult.getFirst() + diceResult.getSecond();

    auto &owner = game.getPlayerByIdForManipulation(tile.getOwnerId());
    currPlayer.subtractBalance(diceResultSum * 10);
    owner.addBalance(diceResultSum * 10);
}

void Chance::handleRailroad(Game &game, Player &currPlayer, const uint8_t railroadTileId) const
{
    currPlayer.setCurrTile(railroadTileId);
    auto &tile = game.getBoardDataForModification().getTilesForModification().at(railroadTileId);
    if (tile.getOwnerId() == currPlayer.getId())
    {
        return;
    }

    if (tile.getOwnerId() == invalidPlayerId)
    {
        if (currPlayer.getCurrentBalance() > tile.getCost() and game.isBuyingTilesEnabled())
        {
            tile.setOwnerId(currPlayer.getId());
            currPlayer.addOwnedTileId(tile.getId());
            currPlayer.subtractBalance(tile.getCost());
        }
        return;
    }

    auto &owner = game.getPlayerByIdForManipulation(tile.getOwnerId());
    const uint8_t numOfRailroadOwned = game.getUtils().getNumOfTilesOfEachTypeOwnedByPlayer(owner, tile);
    const int rentToPay = tile.getRents().at(numOfRailroadOwned - 1);
    owner.addBalance(rentToPay * 2);
    currPlayer.subtractBalance(rentToPay * 2);
}