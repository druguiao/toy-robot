#ifndef _RIGHT_COMMAND_H_
#define _RIGHT_COMMAND_H_

#include "command.h"

class RightCommand: public Command {
    
public:
    RightCommand(): Command() {}
    void execute(Position& position, bool& isPlaced) override;
};

#endif