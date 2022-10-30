#include <gtest/gtest.h>
#include <memory>
#include "../command_parser.h"
#include "../error_codes.h"
#include "../command.h"
#include "../move_command.h"
#include "../left_command.h"
#include "../right_command.h"
#include "../report_command.h"
#include "../position.h"

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

struct CommandParserTest: public ::testing::Test {
    CommandParser* commandParser;
    CommandParserTest()
        : commandParser(new CommandParser)
        {}

    virtual ~CommandParserTest() {
        delete this->commandParser;
    }    
};

TEST_F(CommandParserTest, EmptyString) {
    auto command = commandParser->Parse("");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F(CommandParserTest, UnknownCommand) {
    auto command = commandParser->Parse("123125123");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F(CommandParserTest, PlaceCommandNoArguments) {
    auto command = commandParser->Parse("PLACE");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsEmptyXCoordinate) {
    auto command = commandParser->Parse("PLACE ,0,NORTH");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsInvalidXCoordinate) {
    auto command = commandParser->Parse("PLACE X,0,NORTH");
    EXPECT_EQ(command, nullptr);
    delete command;
}


TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsEmptyYCoordinate) {
    auto command = commandParser->Parse("PLACE 0, ,NORTH");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsEmptyDirection) {
    auto command = commandParser->Parse("PLACE 0,0,");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsNoDirection) {
    auto command = commandParser->Parse("PLACE 0,0");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsDirectionOnly) {
    auto command = commandParser->Parse("PLACE NORTH");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandIncompleteArgumentsCoordinateOnly) {
    auto command = commandParser->Parse("PLACE 1");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandNoSpaces) {
    auto command = commandParser->Parse("PLACE1,1,NORTH");
    EXPECT_EQ(command, nullptr);
    delete command;
}

TEST_F(CommandParserTest, PlaceCommandFilledSpace) {
    auto command = commandParser->Parse("PLACE     1,0,NORTH");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 1);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NORTH);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandWhiteSpaceInYCoordinate) {
    auto command = commandParser->Parse("PLACE 0,0 ,NORTH");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NORTH);
    delete command;
}

TEST_F (CommandParserTest, PlaceCommandWhiteSpaceInXCoordinate) {
    auto command = commandParser->Parse("PLACE 0 ,0,NORTH");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NORTH);
    delete command;
}


TEST_F(CommandParserTest, PlaceCommandWithTrailingWhitespaceOk) {
    auto command = commandParser->Parse(" PLACE 0,0,NORTH ");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_NORTH);
    delete command;
}

TEST_F(CommandParserTest, PlaceCommandDirectionSouth) {
    auto command = commandParser->Parse("PLACE 0,0,SOUTH");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_SOUTH);
    delete command;
}

TEST_F(CommandParserTest, PlaceCommandDirectionEast) {
    auto command = commandParser->Parse("PLACE 0,0,EAST");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_EAST);
    delete command;
}

TEST_F(CommandParserTest, PlaceCommandDirectionWest) {
    auto command = commandParser->Parse("PLACE 0,0,WEST");
    ASSERT_TRUE(command != nullptr);
    auto position = command->getPosition();
    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
    EXPECT_EQ(position.direction, DIRECTION_WEST);
    delete command;
}

TEST_F(CommandParserTest, MoveCommandWithGarbageCharacters) {
    auto command = commandParser->Parse(" MOVE        2312451239 1231");
    ASSERT_TRUE(command == nullptr);
    delete command;
}

TEST_F(CommandParserTest, MoveCommandWithTrailingWhitespaceOK) {
    auto command = commandParser->Parse(" MOVE         ");
    ASSERT_TRUE(command != nullptr);
    ASSERT_TRUE(instanceof<MoveCommand>(command));
    delete command;
}

TEST_F(CommandParserTest, LeftCommandWithGarbageCharacters) {
    auto command = commandParser->Parse(" LEFT        2312451239 1231");
    ASSERT_TRUE(command == nullptr);
    delete command;
}

TEST_F(CommandParserTest, LeftCommandWithTrailingWhitespaceOK) {
    auto command = commandParser->Parse(" LEFT         ");
    ASSERT_TRUE(command != nullptr);
    ASSERT_TRUE(instanceof<LeftCommand>(command));
    delete command;
}

TEST_F(CommandParserTest, RightCommandWithGarbageCharacters) {
    auto command = commandParser->Parse(" RIGHT        2312451239 1231");
    ASSERT_TRUE(command == nullptr);
    delete command;
}

TEST_F(CommandParserTest, RightCommandWithTrailingWhitespaceOK) {
    auto command = commandParser->Parse(" RIGHT         ");
    ASSERT_TRUE(command != nullptr);
    ASSERT_TRUE(instanceof<RightCommand>(command));
    delete command;
}

TEST_F(CommandParserTest, ReportCommandWithGarbageCharacters) {
    auto command = commandParser->Parse(" REPORT        2312451239 1231");
    ASSERT_TRUE(command == nullptr);
    delete command;
}

TEST_F(CommandParserTest, ReportCommandWithTrailingWhitespaceOK) {
    auto command = commandParser->Parse(" REPORT         ");
    ASSERT_TRUE(command != nullptr);
    ASSERT_TRUE(instanceof<ReportCommand>(command));
    delete command;
}

