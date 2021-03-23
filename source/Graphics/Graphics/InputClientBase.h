#ifndef GRAPHICS_INPUT_CLIENT_BASE_H
#define GRAPHICS_INPUT_CLIENT_BASE_H

struct InputClientBase
{
	virtual ~InputClientBase() {}
	virtual bool onMousePressed(double xpos, double ypos, int button) = 0;
	virtual bool onMouseMoved(double xpos, double ypos) = 0;
	virtual bool onMouseReleased(double xpos, double ypos, int button) = 0;
	virtual bool onMouseScrolled(double xoffset, double yoffset) = 0;
	virtual bool onKeyPressed(int key) = 0;
	virtual bool onKeyReleased(int key) = 0;
	virtual bool onWindowSizeChanged(int width, int height) = 0;
};

#endif