#include "Chance.hpp"
#include "Game.hpp"
#include "Player.hpp"

Chance::Chance()
{
	cards.at(0) = Card(
		[](Game &game, Player &currPlayer) {
			currPlayer.setCurrTile(0);
			currPlayer.addBalance(200);
		},
		0);

	cards.at(1) = Card(
		[](Game &game, Player &currPlayer) {
			if (currPlayer.getCurrTile() > 24)
			{
				currPlayer.addBalance(200);
			}
			currPlayer.setCurrTile(24);
		},
		1);

	cards.at(2) = Card(
		[](Game &game, Player &currPlayer) {
			if (currPlayer.getCurrTile() > 11)
			{
				currPlayer.addBalance(200);
			}
			currPlayer.setCurrTile(11);
		},
		2);

	cards.at(3) = Card(
		[](Game &game, Player &currPlayer) {
			// TO DO
		},
		3);

	cards.at(4) = Card(
		[](Game &game, Player &currPlayer) {
			// TO DO
		},
		4);

	cards.at(5) = Card([](Game &game, Player &currPlayer) { currPlayer.addBalance(50); }, 5);

	cards.at(6) = Card([](Game &game, Player &currPlayer) { currPlayer.acquireGetOutOfPrisonCard(); }, 6);

	cards.at(7) = Card([](Game &game, Player &currPlayer) { currPlayer.setCurrTile(currPlayer.getCurrTile() - 3); }, 7);

	cards.at(8) = Card(
		[](Game &game, Player &currPlayer) {
			currPlayer.goToPrison();
			currPlayer.setCurrTile(prisonTile);
		},
		8);

	cards.at(9) = Card(
		[](Game &game, Player &currPlayer) {
			// TO DO make general repairs
		},
		9);

	cards.at(10) = Card(
		[](Game &game, Player &currPlayer) {
			if (currPlayer.getCurrTile() > 5)
			{
				currPlayer.addBalance(200);
			}
			currPlayer.setCurrTile(5);
		},
		10);

	cards.at(11) = Card([](Game &game, Player &currPlayer) { currPlayer.subtractBalance(15); }, 11);

	cards.at(12) = Card([](Game &game, Player &currPlayer) { currPlayer.setCurrTile(39); }, 12);

	cards.at(13) = Card(
		[](Game &game, Player &currPlayer) {
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

	cards.at(14) = Card([](Game &game, Player &currPlayer) { currPlayer.addBalance(150); }, 14);
}

const Card &Chance::getCardById(const uint8_t id) const
{
	return cards.at(id);
}