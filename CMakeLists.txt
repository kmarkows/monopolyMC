cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Monopoly)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(monopoly.exe main.cpp Game.cpp Player.cpp Tile.cpp Board.cpp Card.cpp Chance.cpp CommunityChest.cpp GetOutOfPrisonHandler.cpp Utils.cpp RentPayer.cpp HousesBuilder.cpp Logger.cpp)
add_library(MonopolyLib STATIC main.cpp Game.cpp Player.cpp Tile.cpp Board.cpp Card.cpp Chance.cpp CommunityChest.cpp GetOutOfPrisonHandler.cpp Utils.cpp RentPayer.cpp HousesBuilder.cpp Logger.cpp)

enable_testing()
add_subdirectory(ut)