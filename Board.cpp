#include "Board.hpp"

Board::Board()
{
	tiles.at(0) = Tile("Start", 0, 0);
	tiles.at(1) = Tile("Property", 60, 1);
	tiles.at(2) = Tile("CommunityChest", 0, 2);
	tiles.at(3) = Tile("Property", 60, 3);
	tiles.at(4) = Tile("IncomeTax", 0, 4);
	tiles.at(5) = Tile("Railroad", 200, 5);
	tiles.at(6) = Tile("Property", 100, 6);
	tiles.at(7) = Tile("Chance", 0, 7);
	tiles.at(8) = Tile("Property", 100, 8);
	tiles.at(9) = Tile("Property", 120, 9);
	tiles.at(10) = Tile("Prison", 0, 10);
	tiles.at(11) = Tile("Property", 140, 11);
	tiles.at(12) = Tile("Utilities", 150, 12);
	tiles.at(13) = Tile("Property", 140, 13);
	tiles.at(14) = Tile("Property", 160, 14);
	tiles.at(15) = Tile("Railroad", 200, 15);
	tiles.at(16) = Tile("Property", 180, 16);
	tiles.at(17) = Tile("CommunityChest", 0, 17);
	tiles.at(18) = Tile("Property", 180, 18);
	tiles.at(19) = Tile("Property", 200, 19);
	tiles.at(20) = Tile("Parking", 0, 20);
	tiles.at(21) = Tile("Property", 220, 21);
	tiles.at(22) = Tile("Chance", 0, 22);
	tiles.at(23) = Tile("Property", 220, 23);
	tiles.at(24) = Tile("Property", 240, 24);
	tiles.at(25) = Tile("Railroad", 200, 25);
	tiles.at(26) = Tile("Property", 260, 26);
	tiles.at(27) = Tile("Property", 260, 27);
	tiles.at(28) = Tile("Utilities", 150, 28);
	tiles.at(29) = Tile("Property", 280, 29);
	tiles.at(30) = Tile("GoToPrison", 0, 30);
	tiles.at(31) = Tile("Property", 300, 31);
	tiles.at(32) = Tile("Property", 300, 32);
	tiles.at(33) = Tile("CommunityChest", 0, 33);
	tiles.at(34) = Tile("Property", 320, 34);
	tiles.at(35) = Tile("Railroad", 200, 35);
	tiles.at(36) = Tile("Chance", 320, 36);
	tiles.at(37) = Tile("Property", 350, 37);
	tiles.at(38) = Tile("LuxuryTax", 350, 38);
	tiles.at(39) = Tile("Property", 400, 39);
}

const std::array<Tile, numOfMonopolyBoradTiles> Board::getTiles() const
{
	return tiles;
}

std::array<Tile, numOfMonopolyBoradTiles> &Board::getTilesForModification()
{
	return tiles;
}