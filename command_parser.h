#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

#include <string>
#include <vector>
#include <memory>

#include "command.h"

std::string const STRING_PLACE = "PLACE";
std::string const STRING_MOVE = "MOVE";
std::string const STRING_LEFT = "LEFT";
std::string const STRING_RIGHT = "RIGHT";
std::string const STRING_REPORT = "REPORT";

class CommandParser 
{
public:
    Command* Parse(std::string line);

public:
    std::vector<std::string> split(std::string line, char const delimiter);
    std::string normalize(std::string);
    std::string& trim(std::string&);
    std::string& leftTrim(std::string&);
    std::string& rightTrim(std::string&);
    int parseInt(std::string const&, int&);
    int parseCoordinate(std::string&, int&);
    int parseDirection(std::string&, std::string&);
};


#endif