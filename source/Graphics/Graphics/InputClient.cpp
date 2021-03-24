#include <Graphics/InputClient.h>

struct InputClientImpl
{
	std::function<bool(double, double, int)> mousePressedCallback;
	std::function<bool(double, double)> mouseMovedCallback;
	std::function<bool(double, double, int)> mouseReleasedCallback;
	std::function<bool(double, double)> mouseScrolledCallback;
	std::function<bool(int)> keyPressedCallback;
	std::function<bool(int)> keyReleasedCallback;
	std::function<bool(int, int)> windowResizedCallback;

	InputClientImpl() :
		mousePressedCallback([](double, double, int) { return false; }),
		mouseMovedCallback([](double, double) { return false; }),
		mouseReleasedCallback([](double, double, int) { return false; }),
		mouseScrolledCallback([](double, double) { return false; }),
		keyPressedCallback([](int) { return false; }),
		keyReleasedCallback([](int) { return false; }),
		windowResizedCallback([](int, int) { return false; })
	{}
};

InputClient::InputClient()
{
	data = std::make_shared<InputClientImpl>();
}

bool InputClient::onMousePressed(double xpos, double ypos, int button)
{
	return data->mousePressedCallback(xpos, ypos, button);
}

bool InputClient::onMouseMoved(double xpos, double ypos)
{
	return data->mouseMovedCallback(xpos, ypos);
}

bool InputClient::onMouseReleased(double xpos, double ypos, int button)
{
	return data->mouseReleasedCallback(xpos, ypos, button);
}

bool InputClient::onMouseScrolled(double xoffset, double yoffset)
{
	return data->mouseScrolledCallback(xoffset, yoffset);
}

bool InputClient::onKeyPressed(int key)
{
	return data->keyPressedCallback(key);
}

bool InputClient::onKeyReleased(int key)
{
	return data->keyReleasedCallback(key);
}

bool InputClient::onWindowSizeChanged(int width, int height)
{
	return data->windowResizedCallback(width, height);
}

InputClient& InputClient::onMousePressed(std::function<bool(double, double, int)> callback)
{
	data->mousePressedCallback = callback;
	return *this;
}

InputClient& InputClient::onMouseMoved(std::function<bool(double, double)> callback)
{
	data->mouseMovedCallback = callback;
	return *this;
}

InputClient& InputClient::onMouseReleased(std::function<bool(double, double, int)> callback)
{
	data->mouseReleasedCallback = callback;
	return *this;
}

InputClient& InputClient::onMouseScrolled(std::function<bool(double, double)> callback)
{
	data->mouseScrolledCallback = callback;
	return *this;
}

InputClient& InputClient::onKeyPressed(std::function<bool(int)> callback)
{
	data->keyPressedCallback = callback;
	return *this;
}

InputClient& InputClient::onKeyReleased(std::function<bool(int)> callback)
{
	data->keyReleasedCallback = callback;
	return *this;
}

InputClient& InputClient::onWindowSizeChanged(std::function<bool(int, int)> callback)
{
	data->windowResizedCallback = callback;
	return *this;
}