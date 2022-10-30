#include <iostream>
#include "move_command.h"

void MoveCommand::execute(Position& position, bool& isPlaced) {
    // Ignore until a Place command is issued
    // 
    if (!isPlaced) return;

    // Determine displacement based on direction
    // 
    int xDisplacement = 0;
    int yDisplacement = 0;
    if (position.direction == DIRECTION_NORTH) 
    {
        yDisplacement = 1;
    } else if (position.direction == DIRECTION_EAST) 
    {
        xDisplacement = 1;
    } else if (position.direction == DIRECTION_WEST)
    {
        xDisplacement = -1;
    } else if (position.direction == DIRECTION_SOUTH)
    {
        yDisplacement = -1;
    }
    Position newPosition = {position.x + xDisplacement,
        position.y + yDisplacement, position.direction};

    // Check whether the supposed position is still
    // within bounds
    // 
    if (!this->isWithinBounds(newPosition)) {
        return;
    }

    position = newPosition;
}