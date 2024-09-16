cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

add_executable(TestGame TestGame.cpp)
target_link_libraries(TestGame
    gtest_main
    gtest
    Monopoly
)

add_test(
    NAME TestGame
    COMMAND TestGame
)

add_executable(TestChance TestChance.cpp)
target_link_libraries(TestChance
    gtest_main
    gtest
    Monopoly
)

add_test(
    NAME TestChance
    COMMAND TestChance
)

add_executable(TestCommunityChest TestCommunityChest.cpp)
target_link_libraries(TestCommunityChest
    gtest_main
    gtest
    Monopoly
)

add_test(
    NAME TestCommunityChest
    COMMAND TestCommunityChest
)

add_executable(TestGetOutOfPrisonHandler TestGetOutOfPrisonHandler.cpp)
target_link_libraries(TestGetOutOfPrisonHandler
    gtest_main
    gtest
    Monopoly
)

add_test(
    NAME TestGetOutOfPrisonHandler
    COMMAND TestGetOutOfPrisonHandler
)
