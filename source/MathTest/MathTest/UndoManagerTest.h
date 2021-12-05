#ifndef UNDO_MANAGER_TEST
#define UNDO_MANAGER_TEST

#include <gtest/gtest.h>
#include <Utility/Command.h>
#include <Utility/UndoManager.h>


TEST(Utility, CommandTest)
{
	int value = 0;
	Command command;
	command.onApply([&value]() 
	{
		value = 10;
	});
	command.onUndo([&value]() 
	{
		value = 0;
	});
	EXPECT_EQ(value, 0);
	command.apply();
	EXPECT_EQ(value, 10);
	command.undo();
	EXPECT_EQ(value, 0);
}

TEST(Utility, UndoManagerTest)
{
	UndoManager undoManager;
	int value = 0;
	std::shared_ptr<Command> command = std::make_shared<Command>();
	command->onApply([&value]() 
	{
		value = 10;
	});
	command->onUndo([&value]() 
	{
		value = 0;
	});
	EXPECT_FALSE(undoManager.hasRedoOperations());
	undoManager.applyCommand(command);
	EXPECT_EQ(value, 10);
	EXPECT_FALSE(undoManager.hasRedoOperations());
	undoManager.undo();
	EXPECT_TRUE(undoManager.hasRedoOperations());

}


#endif