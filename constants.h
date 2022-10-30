#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "string"

std::string const ARG_TOKEN_SHORT_FORM_INPUT="-i";
std::string const ARG_TOKEN_LONG_FORM_INPUT="-input";

int const BOARD_WIDTH = 5;
int const BOARD_LENGTH = 5;

int const NUM_OF_ARGS_COMMAND_PLACE = 3;
int const ARG_COMMAND_PLACE_X_COORDINATE = 0;
int const ARG_COMMAND_PLACE_Y_COORDINATE = 1;
int const ARG_COMMAND_PLACE_DIRECTION = 2;

char const ARG_COMMAND_PLACE_DELIMITER = ',';

std::string const DIRECTION_NORTH = "NORTH";
std::string const DIRECTION_EAST = "EAST";
std::string const DIRECTION_WEST = "WEST";
std::string const DIRECTION_SOUTH = "SOUTH";
std::string const DIRECTION_NONE = "NONE";

#endif