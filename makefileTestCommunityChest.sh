g++ -std=c++17 ut/TestCommunityChest.cpp Player.cpp Tile.cpp Board.cpp Card.cpp Game.cpp GetOutOfPrisonHandler.cpp -lgtest -lgtest_main -pthread -o TestCommunityChest
./TestCommunityChest
rm TestCommunityChest