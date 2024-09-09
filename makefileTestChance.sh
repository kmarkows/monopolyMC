g++ -std=c++17 ut/TestChance.cpp Player.cpp Tile.cpp Board.cpp Card.cpp -lgtest -lgtest_main -pthread -o TestChance
./TestChance
rm TestChance