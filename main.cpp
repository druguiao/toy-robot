#include <map>
#include <stdio.h>
#include <iostream>
#include <istream>
#include <fstream>
#include "command_parser.h"
#include "error_codes.h"
#include "toy_robot.h"
#include "constants.h"

int main(int argCount, char *argv[]) {

    // Retrieve args from command line
    // 
    std::map<std::string, std::string> args;
    for (int i = 0; i < argCount; i++)
    {

        std::string token = argv[i];
        if (token == ARG_TOKEN_SHORT_FORM_INPUT || token == ARG_TOKEN_SHORT_FORM_INPUT)
        {
            if( i + 1 < argCount)
            {
                args[ARG_TOKEN_SHORT_FORM_INPUT] = argv[i + 1];
                continue;
            }
            std::cout << "ERROR: -i arg is used but no value is found" << std::endl;
            return -1;
        }
    }
    std::string inputFile = args[ARG_TOKEN_SHORT_FORM_INPUT];
    
    CommandParser commandParser;
    ToyRobot toyRobot;
    
    // Get input from file
    // 
    if (inputFile != "") {
        std::ifstream file(inputFile);
        if (file.is_open()) {
            std::string line = "";
            while (std::getline(file, line)) {
                auto command = commandParser.Parse(line);
                toyRobot.execute(command);
                delete command;
            }

            file.close();
            return 0;
        }
        std::cout << "Error loading input file: '" << inputFile << "'" << std::endl;
        return -1;
    }

    // Get input from command line
    // 
    std::string line = "";
    while (true) {
        std::cout << "Enter a command: " ;
        std::getline(std::cin, line);

        if (line == "") {
            return 0;
        }

        auto command = commandParser.Parse(line);
        toyRobot.execute(command);
        delete command;
    }

    return 0;
}