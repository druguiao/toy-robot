#ifndef _MOVE_COMMAND_H_
#define _MOVE_COMMAND_H_

#include "command.h"

class MoveCommand: public Command {
    
public:
    MoveCommand(): Command() {}
    void execute(Position& position, bool& isPlaced) override;
};

#endif