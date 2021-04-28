#include <Utility/UndoManager.h>

struct UndoManagerImpl
{
	//todo: implement
};

UndoManager::UndoManager()
{
	data = std::make_unique<UndoManagerImpl>();
}

void UndoManager::applyCommand(std::shared_ptr<CommandBase> command)
{
	//todo: implement
}

void UndoManager::undo()
{
	//todo: implement
}

void UndoManager::redo()
{
	//todo: implement
}

void UndoManager::setUndoDepth()
{
	//todo: implement
}

bool UndoManager::hasRedoOperations()
{
	//todo: implement
	return false;
}