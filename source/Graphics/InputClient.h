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

	void onMousePressed(std::function<bool(double, double, int)> callback);
	void onMouseMoved(std::function<bool(double, double)> callback);
	void onMouseReleased(std::function<bool(double, double, int)> callback);
	void onKeyPressed(std::function<bool(int)> callback);
	void onKeyReleased(std::function<bool(int)> callback);
private: 
	std::shared_ptr<InputClientImpl> data;
};

#endif