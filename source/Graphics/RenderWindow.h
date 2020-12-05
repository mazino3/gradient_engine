#ifndef GRAPHICS_RENDER_WINDOW_H
#define GRAPHICS_RENDER_WINDOW_H

#include <memory>
#include <string>
#include "RenderTarget.h"
#include "InputServer.h"

struct RenderWindowImpl;

struct RenderWindow : RenderTarget
{
	RenderWindow(int width, int height, const std::string& name);
	~RenderWindow();
	bool init() override;
	void bind() override;
	bool isOpen();
	void swapBuffers();
	InputServer& getInput();

private:

	std::shared_ptr<RenderWindowImpl> _data;
};

#endif