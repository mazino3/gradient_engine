#ifndef UTILITY_COMMAND_H
#define UTILITY_COMMAND_H

#include <functional>
#include <memory>

struct CommandBase
{
	virtual void apply() = 0;
	virtual void undo() = 0;

	virtual ~CommandBase() {}
};

struct CommandImpl;

struct Command : CommandBase
{
	Command();
	~Command();

	void apply() override;
	void undo() override;

	void onApply(std::function<void(void)> callback);
	void onUndo(std::function<void(void)> callback);
private:
	std::unique_ptr<CommandImpl> data;
};

#endif