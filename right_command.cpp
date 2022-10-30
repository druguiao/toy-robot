#include "right_command.h"

void RightCommand::execute(Position& position, bool& isPlaced) 
{
    // Ignore until a Place command is issued
    // 
    if (!isPlaced) {
        return;
    }

     // Do nothing if direction is not supported/none
    // 
    if (position.direction == DIRECTION_NONE) {
        return;
    }

    if (position.direction == DIRECTION_NORTH)
    {
        position.direction = DIRECTION_EAST;
        return;
    }
    
    if (position.direction == DIRECTION_WEST)
    {
        position.direction = DIRECTION_NORTH;
        return;
    }

    if (position.direction == DIRECTION_SOUTH)
    {
        position.direction = DIRECTION_WEST;
        return;
    }

    if (position.direction == DIRECTION_EAST)
    {
        position.direction = DIRECTION_SOUTH;
        return;
    }
}