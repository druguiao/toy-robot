#ifndef _REPORT_COMMAND_H_
#define _REPORT_COMMAND_H_

#include "command.h"

class ReportCommand: public Command {
    
public:
    ReportCommand(): Command() {}
    void execute(Position& position, bool& isPlaced) override;
};

#endif