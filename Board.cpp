#include "Board.hpp"

Board::Board()
{
	tiles.at(0) = Tile("Start", 0);
	tiles.at(1) = Tile("Property", 60);
	tiles.at(2) = Tile("CommunityChest", 0);
	tiles.at(3) = Tile("Property", 60);
	tiles.at(4) = Tile("IncomeTax", 0);
	tiles.at(5) = Tile("Railroad", 200);
	tiles.at(6) = Tile("Property", 100);
	tiles.at(7) = Tile("Chance", 0);
	tiles.at(8) = Tile("Property", 100);
	tiles.at(9) = Tile("Property", 120);
	tiles.at(10) = Tile("Prison", 0);
	tiles.at(11) = Tile("Property", 140);
	tiles.at(12) = Tile("Utilities", 150);
	tiles.at(13) = Tile("Property", 140);
	tiles.at(14) = Tile("Property", 160);
	tiles.at(15) = Tile("Railroad", 200);
	tiles.at(16) = Tile("Property", 180);
	tiles.at(17) = Tile("CommunityChest", 0);
	tiles.at(18) = Tile("Property", 180);
	tiles.at(19) = Tile("Property", 200);
	tiles.at(20) = Tile("Parking", 0);
	tiles.at(21) = Tile("Property", 220);
	tiles.at(22) = Tile("Chance", 0);
	tiles.at(23) = Tile("Property", 220);
	tiles.at(24) = Tile("Property", 240);
	tiles.at(25) = Tile("Railroad", 200);
	tiles.at(26) = Tile("Property", 260);
	tiles.at(27) = Tile("Property", 260);
	tiles.at(28) = Tile("Utilities", 150);
	tiles.at(29) = Tile("Property", 280);
	tiles.at(30) = Tile("GoToPrison", 0);
	tiles.at(31) = Tile("Property", 300);
	tiles.at(32) = Tile("Property", 300);
	tiles.at(33) = Tile("CommunityChest", 0);
	tiles.at(34) = Tile("Property", 320);
	tiles.at(35) = Tile("Railroad", 200);
	tiles.at(36) = Tile("Chance", 320);
	tiles.at(37) = Tile("Property", 350);
	tiles.at(38) = Tile("LuxuryTax", 350);
	tiles.at(39) = Tile("Property", 400);
}

const std::array<Tile, numOfMonopolyBoradTiles> Board::getTiles() const
{
	return tiles;
}

std::array<Tile, numOfMonopolyBoradTiles> &Board::getTilesForModification()
{
	return tiles;
}