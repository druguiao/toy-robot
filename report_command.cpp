#include "report_command.h"
#include "iostream"

void ReportCommand::execute(Position& position, bool& isPlaced) 
{
    // Ignore until a Place command is issued
    // 
    if (!isPlaced) {
        return;
    }

    std::printf("Position[x: %d, y: %d, dir: %s]\n", position.x, position.y, position.direction.c_str());
}