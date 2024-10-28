#include "CommunityChest.hpp"
#include "DiceThrower.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include "Player.hpp"

CommunityChest::CommunityChest()
{
    cards.at(0) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.setCurrTile(0);
            currPlayer.addBalance(200);
        },
        0);

    cards.at(1) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(200); }, 1);

    cards.at(2) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.subtractBalance(50); }, 2);

    cards.at(3) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(50); }, 3);

    cards.at(4) = Card(
        [this](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.acquireGetOutOfPrisonCommunityChestCard();
            isGetOutOfPrisonCardAvailable = false;
        },
        4);

    cards.at(5) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            currPlayer.goToPrison();
            currPlayer.setCurrTile(prisonTile);
        },
        5);

    cards.at(6) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) {
            for (auto &player : game.getPlayersDataForManipulation())
            {
                if (player.getId() != currPlayer.getId())
                {
                    player.subtractBalance(50);
                    currPlayer.addBalance(50);
                }
            }
        },
        6);

    cards.at(7) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(100); }, 7);

    cards.at(8) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(20); }, 8);

    cards.at(9) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(10); }, 9);

    cards.at(10) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(100); }, 10);

    cards.at(11) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.subtractBalance(50); }, 11);

    cards.at(12) = Card(
        [](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.subtractBalance(50); }, 12);

    cards.at(13) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(25); }, 13);

    cards.at(14) = Card(
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
            int totalRepairCost = numOfHouses * 40 + numOfHotels * 115;
            currPlayer.subtractBalance(totalRepairCost);
        },
        14);

    cards.at(15) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(10); }, 15);

    cards.at(16) =
        Card([](Game &game, Player &currPlayer, const DiceThrower *diceThrower) { currPlayer.addBalance(100); }, 16);
}

void CommunityChest::playNextCard(Game &game, Player &player, const DiceThrower *diceThrower)
{
    if (not isGetOutOfPrisonCardAvailable and nextCardIdToBePlayed == 4)
    {
        nextCardIdToBePlayed++;
    }
    Logger logger;
    logger.logDrawCardCommunityChest(player, nextCardIdToBePlayed);

    cards.at(nextCardIdToBePlayed).doAction(game, player, diceThrower);
    nextCardIdToBePlayed++;
    nextCardIdToBePlayed = nextCardIdToBePlayed % communityChestCardsNumber;
}

void CommunityChest::setNextCardIdToBePlayed(const uint8_t givenNextCardIdToBePlayed)
{
    nextCardIdToBePlayed = givenNextCardIdToBePlayed;
}

void CommunityChest::setIsGetOutOfPrisonCardAvailable(const uint8_t givenIsGetOutOfPrisonCardAvailable)
{
    isGetOutOfPrisonCardAvailable = givenIsGetOutOfPrisonCardAvailable;
}

const Card &CommunityChest::getCardById(const uint8_t id) const
{
    return cards.at(id);
}

const uint8_t CommunityChest::getNextCardIdToBePlayed() const
{
    return nextCardIdToBePlayed;
}

const bool CommunityChest::getIsGetOutOfPrisonCardAvailable() const
{
    return isGetOutOfPrisonCardAvailable;
}
