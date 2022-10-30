#ifndef _TOY_ROBOT_H_
#define _TOY_ROBOT_H_

#include <utility>
#include <string>
#include "command.h"
#include "position.h"

class ToyRobot {
public:
    ToyRobot(){}
    ~ToyRobot(){}

    int execute(Command* command);
    Position const& getCurrentPosition();
    bool const& isPlaced();
    void setIsPlaced(bool const);

private:
    Position m_currentPosition = {0,0, DIRECTION_NONE};
    bool m_isPlaced = false;
};


#endif 