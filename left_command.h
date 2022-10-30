#ifndef _LEFT_COMMAND_H_
#define _LEFT_COMMAND_H_

#include "command.h"

class LeftCommand: public Command {
    
public:
    LeftCommand(): Command() {}
    void execute(Position& position, bool& isPlaced) override;
};

#endif