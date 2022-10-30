#include <iostream>
#include "place_command.h"
#include "constants.h"

void PlaceCommand::execute(Position& position, bool& isPlaced)
{
    // Check if the command's position is out of bounds
    // 
    if (!isWithinBounds(this->position)) {
        return;
    }
    
    position = this->position;
    isPlaced = true;
}