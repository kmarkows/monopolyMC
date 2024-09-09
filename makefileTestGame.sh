g++ -std=c++17 ut/TestGame.cpp Player.cpp Tile.cpp Board.cpp Card.cpp Chance.cpp GetOutOfPrisonHandler.cpp -lgtest -lgtest_main -pthread -o TestGame
./TestGame
rm TestGame