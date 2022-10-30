#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "constants.h"
#include "position.h"

class Command
{   
public:
    Command();
    Command(Position const& position);
    virtual ~Command(){}
    
    virtual void execute(Position& position, bool& isPlaced);

    Position const& getPosition();
    bool const isWithinBounds(Position const position);

protected:
    Position position = {0, 0, DIRECTION_NONE};
};



#endif