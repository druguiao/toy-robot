cmake_minimum_required(VERSION 3.8)

set(This toy-robot)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)


set(Headers
    command.h
    command_parser.h
    constants.h
    error_codes.h
    place_command.h
    left_command.h
    right_command.h
    move_command.h
    report_command.h
    position.h
    toy_robot.h
)
set(Sources
    command.cpp
    command_parser.cpp
    main.cpp
    place_command.cpp
    left_command.cpp
    right_command.cpp
    move_command.cpp
    report_command.cpp
    toy_robot.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)