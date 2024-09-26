#include "Board.hpp"

Board::Board()
{
    tiles.at(0) = Tile("Start", 0, {}, 0, 0);
    tiles.at(1) = Tile("Property", 60, {2, 10, 30, 90, 160, 250}, 50, 1);
    tiles.at(2) = Tile("CommunityChest", 0, {}, 0, 2);
    tiles.at(3) = Tile("Property", 60, {4, 20, 60, 180, 320, 450}, 50, 3);
    tiles.at(4) = Tile("IncomeTax", 0, {}, 0, 4);
    tiles.at(5) = Tile("Railroad", 200, {25, 50, 100, 200}, 0, 5);
    tiles.at(6) = Tile("Property", 100, {6, 30, 90, 270, 400, 550}, 50, 6);
    tiles.at(7) = Tile("Chance", 0, {}, 0, 7);
    tiles.at(8) = Tile("Property", 100, {6, 30, 90, 270, 400, 550}, 50, 8);
    tiles.at(9) = Tile("Property", 120, {8, 40, 100, 300, 450, 600}, 50, 9);
    tiles.at(10) = Tile("Prison", 0, {}, 0, 10);
    tiles.at(11) = Tile("Property", 140, {10, 50, 150, 450, 625, 750}, 100, 11);
    tiles.at(12) = Tile("Utilities", 150, {4, 10}, 0, 12);
    tiles.at(13) = Tile("Property", 140, {10, 50, 150, 450, 625, 750}, 100, 13);
    tiles.at(14) = Tile("Property", 160, {12, 60, 180, 500, 700, 900}, 100, 14);
    tiles.at(15) = Tile("Railroad", 200, {25, 50, 100, 200}, 0, 15);
    tiles.at(16) = Tile("Property", 180, {14, 70, 200, 550, 750, 950}, 100, 16);
    tiles.at(17) = Tile("CommunityChest", 0, {}, 0, 17);
    tiles.at(18) = Tile("Property", 180, {14, 70, 200, 550, 750, 950}, 100, 18);
    tiles.at(19) = Tile("Property", 200, {16, 80, 220, 600, 800, 1000}, 100, 19);
    tiles.at(20) = Tile("Parking", 0, {}, 0, 20);
    tiles.at(21) = Tile("Property", 220, {18, 90, 250, 700, 875, 1050}, 150, 21);
    tiles.at(22) = Tile("Chance", 0, {}, 0, 22);
    tiles.at(23) = Tile("Property", 220, {18, 90, 250, 700, 875, 1050}, 150, 23);
    tiles.at(24) = Tile("Property", 240, {20, 100, 300, 750, 925, 1100}, 150, 24);
    tiles.at(25) = Tile("Railroad", 200, {25, 50, 100, 200}, 0, 25);
    tiles.at(26) = Tile("Property", 260, {22, 110, 330, 800, 975, 1150}, 150, 26);
    tiles.at(27) = Tile("Property", 260, {22, 110, 330, 800, 975, 1150}, 150, 27);
    tiles.at(28) = Tile("Utilities", 150, {4, 10}, 0, 28);
    tiles.at(29) = Tile("Property", 280, {24, 120, 360, 850, 1025, 1200}, 150, 29);
    tiles.at(30) = Tile("GoToPrison", 0, {}, 0, 30);
    tiles.at(31) = Tile("Property", 300, {26, 130, 390, 900, 1100, 1275}, 200, 31);
    tiles.at(32) = Tile("Property", 300, {26, 130, 390, 900, 1100, 1275}, 200, 32);
    tiles.at(33) = Tile("CommunityChest", 0, {}, 0, 33);
    tiles.at(34) = Tile("Property", 320, {28, 150, 450, 1000, 1200, 1400}, 200, 34);
    tiles.at(35) = Tile("Railroad", 200, {25, 50, 100, 200}, 0, 35);
    tiles.at(36) = Tile("Chance", 320, {}, 0, 36);
    tiles.at(37) = Tile("Property", 350, {35, 175, 500, 1100, 1300, 1500}, 200, 37);
    tiles.at(38) = Tile("LuxuryTax", 350, {}, 0, 38);
    tiles.at(39) = Tile("Property", 400, {50, 200, 600, 1400, 1700, 2000}, 200, 39);
}

const std::array<Tile, numOfMonopolyBoradTiles> &Board::getTiles() const
{
    return tiles;
}

std::array<Tile, numOfMonopolyBoradTiles> &Board::getTilesForModification()
{
    return tiles;
}