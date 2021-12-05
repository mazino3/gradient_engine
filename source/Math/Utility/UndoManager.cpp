#include <Utility/UndoManager.h>
#include <vector>

struct UndoManagerImpl
{
	std::vector<std::shared_ptr<CommandBase>> undoRedoStack;
	int commandsToRedo;

	UndoManagerImpl();
};

UndoManagerImpl::UndoManagerImpl() :
	commandsToRedo(0)
{}

UndoManager::UndoManager()
{
	data = std::make_unique<UndoManagerImpl>();
}

UndoManager::~UndoManager() = default;

void UndoManager::applyCommand(std::shared_ptr<CommandBase> command)
{
	command->apply();
	data->undoRedoStack.resize(data->undoRedoStack.size() - data->commandsToRedo);
	data->commandsToRedo = 0;
	data->undoRedoStack.push_back(command);
}

void UndoManager::undo()
{
	if (data->undoRedoStack.size() == data->commandsToRedo)
	{
		return;
	}
	auto command = data->undoRedoStack[data->undoRedoStack.size() - 1 - data->commandsToRedo];
	command->undo();
	data->commandsToRedo++;
}

void UndoManager::redo()
{
	if (data->commandsToRedo <= 0)
	{
		return;
	}
	auto command = data->undoRedoStack[data->undoRedoStack.size() - data->commandsToRedo];
	command->apply();
	data->commandsToRedo--;
}

void UndoManager::setUndoDepth()
{
	//todo: implement
}

bool UndoManager::hasRedoOperations()
{
	return data->commandsToRedo > 0;
}