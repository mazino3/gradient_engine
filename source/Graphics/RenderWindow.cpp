#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "RenderWindow.h"
#include <iostream>


struct RenderWindowImpl
{
	int width;
	int height;
	std::string name;
	bool initCalled;
	GLFWwindow* window;

	RenderWindowImpl(int width, int height, const std::string& name) :
		width(width),
		height(height),
		name(name),
		initCalled(false),
		window(nullptr)
	{}
};

RenderWindow::RenderWindow(int width, int height, const std::string& name)
{
	_data = std::make_shared<RenderWindowImpl>(width, height, name);
}

RenderWindow::~RenderWindow()
{
	if (!_data->initCalled) return;
	glfwTerminate();
}

bool RenderWindow::init()
{
	if (!glfwInit())
	{
		return false;
	}

	_data->window = glfwCreateWindow(_data->width, _data->height, _data->name.c_str(), nullptr, nullptr);
	if (_data->window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_data->window);

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "failed to init glew" << std::endl;
        return false;
    }

	_data->initCalled = true;
	return true;
}

bool RenderWindow::isOpen()
{
	return !glfwWindowShouldClose(_data->window);
}

void RenderWindow::swapBuffers()
{
	glfwSwapBuffers(_data->window);
	glfwPollEvents();
}

void RenderWindow::bind()
{
	//todo: unbind framebuffer from RenderTexture
}

