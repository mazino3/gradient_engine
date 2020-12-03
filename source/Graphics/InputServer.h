#ifndef GRAPHICS_INPUT_SERVER_H
#define GRAPHICS_INPUT_SERVER_H

#include "InputClientBase.h"
#include <memory>

struct InputServerImpl;

struct InputServer
{
	InputServer();

	void addInputClient(InputClientBase& inputClient, float priority);
	void removeInputClient(InputClientBase& inputClient);

	void fireMousePressed(double xpos, double ypos, int button);
	void fireMouseMoved(double xpos, double ypos);
	void fireMouseReleased(double xpos, double ypos, int button);
	void fireKeyPressed(int key);
	void fireKeyReleased(int key);
private:
	std::shared_ptr<InputServerImpl> data;
};

#endif