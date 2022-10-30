#include <gtest/gtest.h>
#include "../toy_robot.h"
#include "../command.h"
#include "../move_command.h"
#include "../left_command.h"
#include "../right_command.h"
#include "../report_command.h"
#include "../place_command.h"
#include "../position.h"
#include "../error_codes.h"

struct ToyRobotUnplacedTest: public ::testing::Test {
    ToyRobot* toyRobot;

    ToyRobotUnplacedTest()
        : toyRobot(new ToyRobot){
            this->toyRobot->setIsPlaced(false);
        }

    virtual ~ToyRobotUnplacedTest() {
        delete this->toyRobot;
    }
};

struct ToyRobotPlacedTest: public ::testing::Test {
    ToyRobot* toyRobot;

    ToyRobotPlacedTest()
        : toyRobot(new ToyRobot){
            this->toyRobot->setIsPlaced(true);
        }

    virtual ~ToyRobotPlacedTest() {
        delete this->toyRobot;
    }
};

TEST_F(ToyRobotUnplacedTest, NullCommand) {
    Command* command = nullptr;
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, ERROR_ROBOT_FAILED_TO_EXECUTE);
    
    auto position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, MoveCommandIgnore) {
    Command* command = new MoveCommand();
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, LeftCommandIgnore) {
    Command* command = new LeftCommand();
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, RightCommandIgnore) {
    Command* command = new RightCommand();
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, ReportCommandIgnore) {
    Command* command = new ReportCommand();
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, MultipleCommandsIgnore) {
    Command* command = new ReportCommand();
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    position = toyRobot->getCurrentPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NONE);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceCommandOutsideBounds) {
    Position position = {5,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 0);
    EXPECT_EQ(robotPosition.y, 0);
    EXPECT_EQ(robotPosition.direction, DIRECTION_NONE);
    EXPECT_EQ(toyRobot->isPlaced(), false);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceCommand) {
    Position position = {3,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceThenMove) {
    Position position = {3,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 4);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceThenForceOutOfBounds) {
    Position position = {4,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 4);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    // move the robot 1 step east to check bounds
    // 
    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    // Robot position should be the same
    // 
    robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 4);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceThenMoveThreeTimes) {
    Position position = {0,0,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 0);
    EXPECT_EQ(robotPosition.y, 0);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 0);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceThenLeftRotate) {
    Position position = {3,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_NORTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceEastThenLeftRotateThenMoveNorth) {
    Position position = {3,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 2);
    EXPECT_EQ(robotPosition.direction, DIRECTION_NORTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceSouthThenLeftRotateThenMoveEast) {
    Position position = {3,1,DIRECTION_SOUTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 4);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceWestThenLeftRotateThenMoveSouth) {
    Position position = {3,1,DIRECTION_WEST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 0);
    EXPECT_EQ(robotPosition.direction, DIRECTION_SOUTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceNorthThenLeftRotateThenMoveWest) {
    Position position = {3,1,DIRECTION_NORTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 2);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_WEST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceNorthThenPerform360Left) {
    Position position = {3,1,DIRECTION_NORTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new LeftCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_NORTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

/*
    RIGHT COMMAND TESTS
*/

TEST_F(ToyRobotUnplacedTest, PlaceThenRightRotate) {
    Position position = {3,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
    
    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_SOUTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceEastThenRightRotateThenMoveSouth) {
    Position position = {3,1,DIRECTION_EAST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 0);
    EXPECT_EQ(robotPosition.direction, DIRECTION_SOUTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceSouthThenRightRotateThenMoveWest) {
    Position position = {3,1,DIRECTION_SOUTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 2);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_WEST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceWestThenRightRotateThenMoveNorth) {
    Position position = {3,1,DIRECTION_WEST};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 2);
    EXPECT_EQ(robotPosition.direction, DIRECTION_NORTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceNorthThenRightRotateThenMoveEast) {
    Position position = {3,1,DIRECTION_NORTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new MoveCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 4);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_EAST);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, PlaceNorthThenPerform360Right) {
    Position position = {3,1,DIRECTION_NORTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new RightCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    auto robotPosition = toyRobot->getCurrentPosition();
    EXPECT_EQ(robotPosition.x, 3);
    EXPECT_EQ(robotPosition.y, 1);
    EXPECT_EQ(robotPosition.direction, DIRECTION_NORTH);
    EXPECT_EQ(toyRobot->isPlaced(), true);

    delete command;
}

TEST_F(ToyRobotUnplacedTest, Report) {
    Position position = {3,1,DIRECTION_NORTH};
    Command* command = new PlaceCommand(position);
    auto result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);

    command = new ReportCommand();
    result = toyRobot->execute(command);
    EXPECT_EQ(result, SUCCESS);
}