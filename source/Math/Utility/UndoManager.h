#ifndef UTILITY_UNDO_MANAGER_H
#define UTILITY_UNDO_MANAGER_H

#include <memory>
#include <Utility/Command.h>

struct UndoManagerImpl;

struct UndoManager
{
	UndoManager();

	void applyCommand(std::shared_ptr<CommandBase> command);
	void undo();
	void redo();
	void setUndoDepth();
	bool hasRedoOperations();

private:
	std::unique_ptr<UndoManagerImpl> data;
};

#endif