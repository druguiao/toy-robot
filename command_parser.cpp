
#include <iostream>
#include <vector>
#include <algorithm>
#include "command_parser.h"
#include "error_codes.h"
#include "constants.h"
#include "place_command.h"
#include "move_command.h"
#include "left_command.h"
#include "right_command.h"
#include "report_command.h"
#include "position.h"

Command* CommandParser::Parse(std::string line) {
    if (line == "") return nullptr;

    line = this->normalize(line);

    // Check if PLACE command
    //
    if (line.rfind(STRING_PLACE, 0) == 0) {

        // Isolate PLACE ARGS (<x>,<y>,<direction>)
        // 
        line.erase(0,STRING_PLACE.length());
        if (line.length() == 0) return nullptr; // No args 
        if (line.at(0) != ' ') return nullptr; // Proper delimiter not used

        // Check for coordinate arguments tied to the PLACE command
        // 
        line = this->trim(line);
        auto coordinateTokens = this->split(line, ARG_COMMAND_PLACE_DELIMITER);
        if (coordinateTokens.size() != NUM_OF_ARGS_COMMAND_PLACE) return nullptr; // Insufficient number of args

        // Parse X Coordinate
        // 
        int xCoordinate = 0;
        int result = this->parseCoordinate(coordinateTokens[ARG_COMMAND_PLACE_X_COORDINATE], xCoordinate);
        if (result != SUCCESS) {
            return nullptr;
        }

        // Parse Y Coordinate
        //
        int yCoordinate = 0;
        result = this->parseCoordinate(coordinateTokens[ARG_COMMAND_PLACE_Y_COORDINATE], yCoordinate);
        if (result != SUCCESS) {
            return nullptr;
        }

        // Parse Direction
        // 
        std::string direction = "";
        result = this->parseDirection(coordinateTokens[ARG_COMMAND_PLACE_DIRECTION], direction);
        if (result != SUCCESS) {
            return nullptr;
        }

        Position position = {xCoordinate, yCoordinate, direction};
        return new PlaceCommand(position);
    }

    // Check if MOVE Command
    // 
    if (line == STRING_MOVE) {
        return new MoveCommand();
    }

    // Check if LEFT Command
    // 
    if (line == STRING_LEFT) {
        return new LeftCommand();
    }

    // Check if RIGHT Command
    // 
    if (line == STRING_RIGHT) {
        return new RightCommand();
    }

    // Check if REPORT Command
    // 
    if (line == STRING_REPORT) {
        return new ReportCommand();
    }
    
    return nullptr;
}

std::string CommandParser::normalize(std::string line)
{

    // Set all characters to uppercase for uniformity
    // 
    std::string output = "";
    for (auto val: line) output += toupper(val);

    output = this->trim(output);
    
    return output;
}


std::string & CommandParser::trim(std::string & str)
{
   return this->leftTrim(this->rightTrim(str));
}

std::string & CommandParser::leftTrim(std::string & str)
{
  auto it =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( str.begin() , it);
  return str;   
}

std::string & CommandParser::rightTrim(std::string & str)
{
  auto it =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( it.base() , str.end() );
  return str;   
}

std::vector<std::string> CommandParser::split(std::string line, char const delimiter)
{
    std::vector<std::string> tokens;

    std::string token = "";
    for (auto currentChar: line) {
        if (currentChar == delimiter) {

            tokens.push_back(token);

            token = "";
            
            continue;
        }

        token += currentChar;
    }
    if (token != "" ) {
        tokens.push_back(token);
    }

    return tokens;
}

int CommandParser::parseInt(std::string const& val, int& output)
{

    try {
        output = stoi(val);
    } catch(...) {
        std::cout << "CommandParser::parseInt. Failed to parse: '" << val << "'" <<std::endl;
        return ERROR_PARSE;
    }

    return SUCCESS;
}

int CommandParser::parseCoordinate(std::string& val, int& output) {
    return this->parseInt(this->trim(val), output);
}

int CommandParser::parseDirection(std::string& val, std::string& output) {
    
    output = this->trim(val);
    if (output == DIRECTION_NORTH ||
        output == DIRECTION_EAST ||
        output == DIRECTION_WEST ||
        output == DIRECTION_SOUTH)
        return SUCCESS;
    
    return ERROR_COMMAND_PLACE_ARGS_INVALID_DIRECTION;
}
