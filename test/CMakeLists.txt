cmake_minimum_required(VERSION 3.8)

set(This toy-robotTests)

set(Sources
    test_command_parser.cpp
    test_toy_robot.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    toy-robot
)

add_test(
    NAME ${This}
    COMMAND ${This}
)