#ifndef _PLACE_COMMAND_H_
#define _PLACE_COMMAND_H_

#include <iostream>
#include "command.h"
#include "position.h"
#include "constants.h"

class PlaceCommand: public Command 
{
public:
    PlaceCommand(Position const& position)
        : Command(position) {}

    ~PlaceCommand(){}
    
    void execute(Position& position, bool& isPlaced) override;
};

#endif