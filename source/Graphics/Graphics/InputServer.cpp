#include <Graphics/InputServer.h>
#include "InputServerEvents.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>



struct InputServerImpl
{
	std::vector<std::pair<InputClientBase*, float> > inputClients;
	std::vector<InputEvent> inputEvents;
};

InputServer::InputServer()
{
	data = std::make_shared<InputServerImpl>();
}

void InputServer::addInputClient(InputClientBase& inputClient, float priority)
{
	auto position = std::find_if(data->inputClients.begin(), data->inputClients.end(), [&](const auto& pair) 
	{
		return pair.first == &inputClient;
	});

	if (position != data->inputClients.end())
	{
		std::cout << "warning: trying to add the same input client twice" << std::endl;
		return;
	}

	data->inputClients.push_back(std::make_pair(&inputClient, priority));
	
	std::sort(data->inputClients.begin(), data->inputClients.end(), [](const auto& p1, const auto& p2) 
	{
		return p1.second < p2.second;
	});
}

void InputServer::removeInputClient(InputClientBase& inputClient)
{
	data->inputClients.erase(std::remove_if(data->inputClients.begin(), data->inputClients.end(), [&](const auto& pair)
	{
		return pair.first == &inputClient;
	}));
}

void InputServer::fireMousePressed(double xpos, double ypos, int button)
{
	InputEvent e;
	e.type = InputEventType::MOUSE_PRESSED;
	e.mousePressed = MousePressedEvent{ xpos, ypos, button };
	data->inputEvents.push_back(e);
}

void InputServer::fireMouseMoved(double xpos, double ypos)
{
	InputEvent e;
	e.type = InputEventType::MOUSE_MOVED;
	e.mouseMoved = MouseMovedEvent{ xpos, ypos };
	data->inputEvents.push_back(e);
}

void InputServer::fireMouseReleased(double xpos, double ypos, int button)
{
	InputEvent e;
	e.type = InputEventType::MOUSE_RELEASED;
	e.mouseReleased = MouseReleasedEvent{ xpos, ypos, button };
	data->inputEvents.push_back(e);
}

void InputServer::fireMouseScrolled(double xoffset, double yoffset)
{
	InputEvent e;
	e.type = InputEventType::MOUSE_SCROLLED;
	e.mouseScrolled = MouseScrolledEvent{ xoffset, yoffset };
	data->inputEvents.push_back(e);
}

void InputServer::fireKeyPressed(int key)
{
	InputEvent e;
	e.type = InputEventType::KEY_PRESSED;
	e.keyPressed = KeyPressedEvent{ key };
	data->inputEvents.push_back(e);
}

void InputServer::fireKeyReleased(int key)
{
	InputEvent e;
	e.type = InputEventType::KEY_RELEASED;
	e.keyReleased = KeyReleasedEvent{ key };
	data->inputEvents.push_back(e);
}

void InputServer::fireWindowSizeChanged(int width, int height)
{
	InputEvent e;
	e.type = InputEventType::WINDOW_SIZE_CHANGED;
	e.windowSizeChanged = WindowSizeChangedEvent{ width, height };
	data->inputEvents.push_back(e);
}

void InputServer::processInput()
{
	for (auto& e : data->inputEvents)
	{
		bool consumed = false;
		for (auto& inputClient : data->inputClients)
		{
			switch (e.type)
			{
				case InputEventType::MOUSE_PRESSED:
					consumed = inputClient.first->onMousePressed(e.mousePressed.xpos, e.mousePressed.ypos, e.mousePressed.button);
					break;
				case InputEventType::MOUSE_RELEASED:
					consumed = inputClient.first->onMouseReleased(e.mouseReleased.xpos, e.mouseReleased.ypos, e.mouseReleased.button);
					break;
				case InputEventType::MOUSE_MOVED:
					consumed = inputClient.first->onMouseMoved(e.mouseMoved.xpos, e.mouseMoved.ypos);
					break;
				case InputEventType::MOUSE_SCROLLED:
					consumed = inputClient.first->onMouseScrolled(e.mouseScrolled.xoffset, e.mouseScrolled.yoffset);
					break;
				case InputEventType::KEY_PRESSED:
					consumed = inputClient.first->onKeyPressed(e.keyPressed.key);
					break;
				case InputEventType::KEY_RELEASED:
					consumed = inputClient.first->onKeyReleased(e.keyReleased.key);
					break;
				case InputEventType::WINDOW_SIZE_CHANGED:
					consumed = inputClient.first->onWindowSizeChanged(e.windowSizeChanged.width, e.windowSizeChanged.height);
					break;
			}

			if (consumed)
			{
				break;
			}
		}
	}

	data->inputEvents.clear();
}
