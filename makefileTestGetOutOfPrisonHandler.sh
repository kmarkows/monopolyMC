g++ -std=c++17 ut/TestGetOutOfPrisonHandler.cpp Player.cpp Board.cpp -lgtest -lgtest_main -pthread -o TestGetOutOfJailHandler
./TestGetOutOfJailHandler
rm TestGetOutOfJailHandler