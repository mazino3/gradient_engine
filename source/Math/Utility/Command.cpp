#include <Utility/Command.h>

struct CommandImpl
{
	std::function<void(void)> applyCallback;
	std::function<void(void)> undoCallback;

	CommandImpl();
};

CommandImpl::CommandImpl() :
	applyCallback([]() {}),
	undoCallback([]() {})
{}

Command::Command()
{
	data = std::make_unique<CommandImpl>();
}

void Command::apply()
{
	data->applyCallback();
}

void Command::undo()
{
	data->undoCallback();
}

void Command::onApply(std::function<void(void)> callback)
{
	data->applyCallback = callback;
}

void Command::onUndo(std::function<void(void)> callback)
{
	data->undoCallback = callback;
}