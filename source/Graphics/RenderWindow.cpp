#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "RenderWindow.h"
#include <iostream>
#include "GlfwKeyCodes.h"


struct RenderWindowImpl
{
	int width;
	int height;
	std::string name;
	bool initCalled;
	GLFWwindow* window;
	InputServer inputServer;

	RenderWindowImpl(int width, int height, const std::string& name) :
		width(width),
		height(height),
		name(name),
		initCalled(false),
		window(nullptr)
	{}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		RenderWindowImpl* renderWindow = (RenderWindowImpl*)glfwGetWindowUserPointer(window);
		
		if (action == GLFW_PRESS)
		{
			renderWindow->inputServer.fireKeyPressed(glfwKeycodeToEngineKeycode(key));
		} 
		else if (action == GLFW_RELEASE)
		{
			renderWindow->inputServer.fireKeyReleased(glfwKeycodeToEngineKeycode(key));
		}
	}

	static void cursorCallback(GLFWwindow* window, double xpos, double ypos)
	{
		RenderWindowImpl* renderWindow = (RenderWindowImpl*)glfwGetWindowUserPointer(window);
		renderWindow->inputServer.fireMouseMoved(xpos, ypos);
	}

	static void mousePressedCallback(GLFWwindow* window, int button, int action, int mods)
	{
		RenderWindowImpl* renderWindow = (RenderWindowImpl*)glfwGetWindowUserPointer(window);
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (action == GLFW_PRESS)
		{
			renderWindow->inputServer.fireMousePressed(xpos, ypos, glfwMouseCodeToEngineMouseCode(button));
		}
		else if (action == GLFW_RELEASE)
		{
			renderWindow->inputServer.fireMouseReleased(xpos, ypos, glfwMouseCodeToEngineMouseCode(button));
		}
	}

	static void mouseScrolledCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		RenderWindowImpl* renderWindow = (RenderWindowImpl*)glfwGetWindowUserPointer(window);
		renderWindow->inputServer.fireMouseScrolled(xoffset, yoffset);
	}
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

	glfwWindowHint(GLFW_SAMPLES, 4);
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	glfwSetWindowUserPointer(_data->window, &(*_data));
	glfwSetKeyCallback(_data->window, RenderWindowImpl::keyCallback);
	glfwSetCursorPosCallback(_data->window, RenderWindowImpl::cursorCallback);
	glfwSetMouseButtonCallback(_data->window, RenderWindowImpl::mousePressedCallback);
	glfwSetScrollCallback(_data->window, RenderWindowImpl::mouseScrolledCallback);

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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, _data->width, _data->height);
}

int RenderWindow::getWidth()
{
	return _data->width;
}

int RenderWindow::getHeight()
{
	return _data->height;
}

InputServer& RenderWindow::getInput()
{
	return _data->inputServer;
}

