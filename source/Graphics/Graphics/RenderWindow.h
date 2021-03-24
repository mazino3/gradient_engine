#ifndef GRAPHICS_RENDER_WINDOW_H
#define GRAPHICS_RENDER_WINDOW_H

#include <memory>
#include <string>
#include <Graphics/RenderTarget.h>
#include <Graphics/InputServer.h>

struct RenderWindowImpl;

struct RenderWindow : RenderTarget
{
	RenderWindow(int width, int height, const std::string& name);
	~RenderWindow();
	bool init() override;
	void bind() override;
	int getWidth() override;
	int getHeight() override;
	bool isOpen();
	void swapBuffers();
	InputServer& getInput();

	//todo: this class should not rely on glfw
	GLFWwindow* getWindowPointer();

private:

	std::shared_ptr<RenderWindowImpl> _data;
};

#endif