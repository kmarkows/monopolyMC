#include "Chance.hpp"
#include "Player.hpp"

Chance::Chance()
{
	cards.at(0) = Card(
		[](Player &player, Board &board) {
			player.setCurrTile(0);
			player.addBalance(200);
		},
		0);

	cards.at(1) = Card(
		[](Player &player, Board &board) {
			if (player.getCurrTile() > 24)
			{
				player.addBalance(200);
			}
			player.setCurrTile(24);
		},
		1);

	cards.at(2) = Card(
		[](Player &player, Board &board) {
			if (player.getCurrTile() > 11)
			{
				player.addBalance(200);
			}
			player.setCurrTile(11);
		},
		2);

	cards.at(3) = Card(
		[](Player &player, Board &board) {
			// TO DO
		},
		3);

	cards.at(4) = Card(
		[](Player &player, Board &board) {
			// TO DO
		},
		4);

	cards.at(5) = Card([](Player &player, Board &board) { player.addBalance(50); }, 5);

	cards.at(6) = Card(
		[](Player &player, Board &board) {
			player.acquireGetOutOfPrisonCard();
		},
		6);

    cards.at(7) = Card(
		[](Player &player, Board &board) {
			// TO DO go back 3 tiles
		},
		7);

    cards.at(8) = Card(
		[](Player &player, Board &board) {
            player.goToPrison();
	        player.setCurrTile(prisonTile);
		},
		8);

    cards.at(9) = Card(
		[](Player &player, Board &board) {
			// TO DO make general repairs
		},
		9);

    cards.at(10) = Card(
		[](Player &player, Board &board) {
            if (player.getCurrTile() > 5)
			{
				player.addBalance(200);
			}
			player.setCurrTile(5);
		},
		10);

    cards.at(11) = Card(
		[](Player &player, Board &board) {
            player.subtractBalance(15);
		},
		11);

    cards.at(12) = Card(
		[](Player &player, Board &board) {
            player.setCurrTile(39);
		},
		12);

    cards.at(13) = Card(
		[](Player &player, Board &board) {
            // TO DO pay every player 50
		},
		13);

    cards.at(14) = Card(
		[](Player &player, Board &board) {
            player.addBalance(150);
		},
		14);
}

const Card &Chance::getCardById(const uint8_t id) const
{
	return cards.at(id);
}