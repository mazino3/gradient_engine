#ifndef INPUT_SERVER_EVENTS_H
#define INPUT_SERVER_EVENTS_H

struct MousePressedEvent
{
	double xpos;
	double ypos;
	int button;
};

struct MouseReleasedEvent
{
	double xpos;
	double ypos;
	int button;
};

struct MouseMovedEvent
{
	double xpos;
	double ypos;
};

struct MouseScrolledEvent
{
	double xoffset;
	double yoffset;
};

struct KeyPressedEvent
{
	int key;
};

struct KeyReleasedEvent
{
	int key;
};

struct WindowSizeChangedEvent
{
	int width;
	int height;
};

enum class InputEventType
{
	MOUSE_PRESSED,
	MOUSE_RELEASED,
	MOUSE_MOVED,
	MOUSE_SCROLLED,
	KEY_PRESSED,
	KEY_RELEASED,
	WINDOW_SIZE_CHANGED
};

struct InputEvent
{
	InputEventType type;

	union
	{
		MousePressedEvent mousePressed;
		MouseReleasedEvent mouseReleased;
		MouseMovedEvent mouseMoved;
		MouseScrolledEvent mouseScrolled;
		KeyPressedEvent keyPressed;
		KeyReleasedEvent keyReleased;
		WindowSizeChangedEvent windowSizeChanged;
	};
};

#endif