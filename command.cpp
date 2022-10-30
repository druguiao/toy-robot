#include <utility>
#include <string>
#include <iostream>

#include "command.h"
#include "position.h"
#include "constants.h"

Command::Command(){}

Command::Command(Position const& position) 
{
    this->position = position;
}

Position const& Command::getPosition()
{
    return this->position;
}

bool const Command::isWithinBounds(Position position)
{
    return position.x >= 0 && position.x < BOARD_WIDTH &&
        position.y >= 0 && position.y < BOARD_LENGTH;
}

void Command::execute(Position& position, bool& isPlaced)
{
    // Do nothing
    // 
}
