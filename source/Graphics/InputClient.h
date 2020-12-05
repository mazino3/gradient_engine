#ifndef GRAPHICS_INPUT_CLIENT_H
#define GRAPHICS_INPUT_CLIENT_H

#include "InputClientBase.h"
#include <functional>
#include <memory>

struct InputClientImpl;

struct InputClient : InputClientBase
{
	InputClient();

	bool onMousePressed(double xpos, double ypos, int button);
	bool onMouseMoved(double xpos, double ypos);
	bool onMouseReleased(double xpos, double ypos, int button);
	bool onKeyPressed(int key);
	bool onKeyReleased(int key);

	InputClient& onMousePressed(std::function<bool(double, double, int)> callback);
	InputClient& onMouseMoved(std::function<bool(double, double)> callback);
	InputClient& onMouseReleased(std::function<bool(double, double, int)> callback);
	InputClient& onKeyPressed(std::function<bool(int)> callback);
	InputClient& onKeyReleased(std::function<bool(int)> callback);
private: 
	std::shared_ptr<InputClientImpl> data;
};

#endif