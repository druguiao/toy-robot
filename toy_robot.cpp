#include <iostream>
#include "toy_robot.h"
#include "error_codes.h"

int ToyRobot::execute(Command* command)
{
    if (command == nullptr) {
        return ERROR_ROBOT_FAILED_TO_EXECUTE;
    }
    command->execute(this->m_currentPosition, this->m_isPlaced);

    return SUCCESS;
}

bool const& ToyRobot::isPlaced() 
{
    return this->m_isPlaced;
}

void ToyRobot::setIsPlaced(bool const value) 
{
    this->m_isPlaced = value;
}

Position const& ToyRobot::getCurrentPosition()
{
    return this->m_currentPosition;
}

