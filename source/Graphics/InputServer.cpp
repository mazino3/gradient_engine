#include "InputServer.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

struct InputServerImpl
{
	std::vector<std::pair<InputClientBase*, float> > inputClients;
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
	std::remove_if(data->inputClients.begin(), data->inputClients.end(), [&](const auto& pair) 
	{
		return pair.first == &inputClient;
	});
}

void InputServer::fireMousePressed(double xpos, double ypos, int button)
{
	//todo: implement
}

void InputServer::fireMouseMoved(double xpos, double ypos)
{
	//todo: implement
}

void InputServer::fireMouseReleased(double xpos, double ypos, int button)
{
	//todo: implement
}

void InputServer::fireKeyPressed(int key)
{
	//todo: implement
}

void InputServer::fireKeyReleased(int key)
{
	//todo: implement
}
