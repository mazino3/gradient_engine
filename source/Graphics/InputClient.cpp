#include "InputClient.h"

struct InputClientImpl
{
	std::function<bool(double, double, int)> mousePressedCallback;
	std::function<bool(double, double)> mouseMovedCallback;
	std::function<bool(double, double, int)> mouseReleasedCallback;
	std::function<bool(int)> keyPressedCallback;
	std::function<bool(int)> keyReleasedCallback;

	InputClientImpl() :
		mousePressedCallback([](double, double, int) { return false; }),
		mouseMovedCallback([](double, double) { return false; }),
		mouseReleasedCallback([](double, double, int) { return false; }),
		keyPressedCallback([](int) { return false; }),
		keyReleasedCallback([](int) { return false; })
	{}
};

InputClient::InputClient()
{
	data = std::make_shared<InputClientImpl>();
}

bool InputClient::onMousePressed(double xpos, double ypos, int button)
{
	data->mousePressedCallback(xpos, ypos, button);
}

bool InputClient::onMouseMoved(double xpos, double ypos)
{
	data->mouseMovedCallback(xpos, ypos);
}

bool InputClient::onMouseReleased(double xpos, double ypos, int button)
{
	data->mouseReleasedCallback(xpos, ypos, button);
}

bool InputClient::onKeyPressed(int key)
{
	data->keyPressedCallback(key);
}

bool InputClient::onKeyReleased(int key)
{
	data->keyReleasedCallback(key);
}

void InputClient::onMousePressed(std::function<bool(double, double, int)> callback)
{
	data->mousePressedCallback = callback;
}

void InputClient::onMouseMoved(std::function<bool(double, double)> callback)
{
	data->mouseMovedCallback = callback;
}

void InputClient::onMouseReleased(std::function<bool(double, double, int)> callback)
{
	data->mouseReleasedCallback = callback;
}

void InputClient::onKeyPressed(std::function<bool(int)> callback)
{
	data->keyPressedCallback = callback;
}

void InputClient::onKeyReleased(std::function<bool(int)> callback)
{
	data->keyReleasedCallback = callback;
}