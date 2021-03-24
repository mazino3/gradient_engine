#ifndef GRAPHICS_GLFW_KEYCODES_H
#define GRAPHICS_GLFW_KEYCODES_H

#include <GLFW/glfw3.h>
#include <Graphics/KeyCodes.h>

int glfwMouseCodeToEngineMouseCode(int glfwKeycode)
{
	switch (glfwKeycode)
	{
		case GLFW_MOUSE_BUTTON_1: return KEYCODE_MOUSE_BUTTON_1;
		case GLFW_MOUSE_BUTTON_2: return KEYCODE_MOUSE_BUTTON_2;
		case GLFW_MOUSE_BUTTON_3: return KEYCODE_MOUSE_BUTTON_3;
		case GLFW_MOUSE_BUTTON_4: return KEYCODE_MOUSE_BUTTON_4;
		case GLFW_MOUSE_BUTTON_5: return KEYCODE_MOUSE_BUTTON_5;
		case GLFW_MOUSE_BUTTON_6: return KEYCODE_MOUSE_BUTTON_6;
		case GLFW_MOUSE_BUTTON_7: return KEYCODE_MOUSE_BUTTON_7;
		case GLFW_MOUSE_BUTTON_8: return KEYCODE_MOUSE_BUTTON_8;
	}
	return glfwKeycode;
}

int glfwKeycodeToEngineKeycode(int glfwKeycode)
{
	switch (glfwKeycode)
	{
		case GLFW_KEY_UNKNOWN:		return KEYCODE_KEY_UNKNOWN;
		case GLFW_KEY_SPACE:		return KEYCODE_KEY_SPACE;
		case GLFW_KEY_APOSTROPHE:	return KEYCODE_KEY_APOSTROPHE;
		case GLFW_KEY_COMMA:		return KEYCODE_KEY_COMMA;
		case GLFW_KEY_MINUS:		return KEYCODE_KEY_MINUS;
		case GLFW_KEY_PERIOD:		return KEYCODE_KEY_PERIOD;
		case GLFW_KEY_SLASH: 		return KEYCODE_KEY_SLASH;
		case GLFW_KEY_0: 			return KEYCODE_KEY_0;
		case GLFW_KEY_1: 			return KEYCODE_KEY_1;
		case GLFW_KEY_2: 			return KEYCODE_KEY_2;
		case GLFW_KEY_3: 			return KEYCODE_KEY_3;
		case GLFW_KEY_4: 			return KEYCODE_KEY_4;
		case GLFW_KEY_5: 			return KEYCODE_KEY_5;
		case GLFW_KEY_6: 			return KEYCODE_KEY_6;
		case GLFW_KEY_7: 			return KEYCODE_KEY_7;
		case GLFW_KEY_8: 			return KEYCODE_KEY_8;
		case GLFW_KEY_9: 			return KEYCODE_KEY_9;
		case GLFW_KEY_SEMICOLON: 	return KEYCODE_KEY_SEMICOLON;
		case GLFW_KEY_EQUAL: 		return KEYCODE_KEY_EQUAL;
		case GLFW_KEY_A: 			return KEYCODE_KEY_A;
		case GLFW_KEY_B: 			return KEYCODE_KEY_B;
		case GLFW_KEY_C: 			return KEYCODE_KEY_C;
		case GLFW_KEY_D:			return KEYCODE_KEY_D;
		case GLFW_KEY_E: 			return KEYCODE_KEY_E;
		case GLFW_KEY_F: 			return KEYCODE_KEY_F;
		case GLFW_KEY_G: 			return KEYCODE_KEY_G;
		case GLFW_KEY_H: 			return KEYCODE_KEY_H;
		case GLFW_KEY_I: 			return KEYCODE_KEY_I;
		case GLFW_KEY_J: 			return KEYCODE_KEY_J;
		case GLFW_KEY_K: 			return KEYCODE_KEY_K;
		case GLFW_KEY_L: 			return KEYCODE_KEY_L;
		case GLFW_KEY_M: 			return KEYCODE_KEY_M;
		case GLFW_KEY_N: 			return KEYCODE_KEY_N;
		case GLFW_KEY_O: 			return KEYCODE_KEY_O;
		case GLFW_KEY_P: 			return KEYCODE_KEY_P;
		case GLFW_KEY_Q: 			return KEYCODE_KEY_Q;
		case GLFW_KEY_R: 			return KEYCODE_KEY_R;
		case GLFW_KEY_S: 			return KEYCODE_KEY_S;
		case GLFW_KEY_T: 			return KEYCODE_KEY_T;
		case GLFW_KEY_U: 			return KEYCODE_KEY_U;
		case GLFW_KEY_V: 			return KEYCODE_KEY_V;
		case GLFW_KEY_W: 			return KEYCODE_KEY_W;
		case GLFW_KEY_X: 			return KEYCODE_KEY_X;
		case GLFW_KEY_Y: 			return KEYCODE_KEY_Y;
		case GLFW_KEY_Z: 			return KEYCODE_KEY_Z;
		case GLFW_KEY_LEFT_BRACKET: return KEYCODE_KEY_LEFT_BRACKET;
		case GLFW_KEY_BACKSLASH: 	return KEYCODE_KEY_BACKSLASH;
		case GLFW_KEY_RIGHT_BRACKET:return KEYCODE_KEY_RIGHT_BRACKET;
		case GLFW_KEY_GRAVE_ACCENT: return KEYCODE_KEY_GRAVE_ACCENT;
		case GLFW_KEY_WORLD_1: 		return KEYCODE_KEY_WORLD_1;
		case GLFW_KEY_WORLD_2: 		return KEYCODE_KEY_WORLD_2;
		case GLFW_KEY_ESCAPE: 		return KEYCODE_KEY_ESCAPE;
		case GLFW_KEY_ENTER: 		return KEYCODE_KEY_ENTER;
		case GLFW_KEY_TAB: 			return KEYCODE_KEY_TAB;
		case GLFW_KEY_BACKSPACE: 	return KEYCODE_KEY_BACKSPACE;
		case GLFW_KEY_INSERT: 		return KEYCODE_KEY_INSERT;
		case GLFW_KEY_DELETE: 		return KEYCODE_KEY_DELETE;
		case GLFW_KEY_RIGHT: 		return KEYCODE_KEY_RIGHT;
		case GLFW_KEY_LEFT: 		return KEYCODE_KEY_LEFT;
		case GLFW_KEY_DOWN: 		return KEYCODE_KEY_DOWN;
		case GLFW_KEY_UP: 			return KEYCODE_KEY_UP;
		case GLFW_KEY_PAGE_UP: 		return KEYCODE_KEY_PAGE_UP;
		case GLFW_KEY_PAGE_DOWN:	return KEYCODE_KEY_PAGE_DOWN;
		case GLFW_KEY_HOME: 		return KEYCODE_KEY_HOME;
		case GLFW_KEY_END: 			return KEYCODE_KEY_END;
		case GLFW_KEY_CAPS_LOCK: 	return KEYCODE_KEY_CAPS_LOCK;
		case GLFW_KEY_SCROLL_LOCK: 	return KEYCODE_KEY_SCROLL_LOCK;
		case GLFW_KEY_NUM_LOCK: 	return KEYCODE_KEY_NUM_LOCK;
		case GLFW_KEY_PRINT_SCREEN:	return KEYCODE_KEY_PRINT_SCREEN;
		case GLFW_KEY_PAUSE: 		return KEYCODE_KEY_PAUSE;
		case GLFW_KEY_F1: 			return KEYCODE_KEY_F1;
		case GLFW_KEY_F2: 			return KEYCODE_KEY_F2;
		case GLFW_KEY_F3: 			return KEYCODE_KEY_F3;
		case GLFW_KEY_F4: 			return KEYCODE_KEY_F4;
		case GLFW_KEY_F5: 			return KEYCODE_KEY_F5;
		case GLFW_KEY_F6: 			return KEYCODE_KEY_F6;
		case GLFW_KEY_F7: 			return KEYCODE_KEY_F7;
		case GLFW_KEY_F8: 			return KEYCODE_KEY_F8;
		case GLFW_KEY_F9: 			return KEYCODE_KEY_F9;
		case GLFW_KEY_F10: 			return KEYCODE_KEY_F10;
		case GLFW_KEY_F11: 			return KEYCODE_KEY_F11;
		case GLFW_KEY_F12: 			return KEYCODE_KEY_F12;
		case GLFW_KEY_F13: 			return KEYCODE_KEY_F13;
		case GLFW_KEY_F14: 			return KEYCODE_KEY_F14;
		case GLFW_KEY_F15: 			return KEYCODE_KEY_F15;
		case GLFW_KEY_F16: 			return KEYCODE_KEY_F16;
		case GLFW_KEY_F17: 			return KEYCODE_KEY_F17;
		case GLFW_KEY_F18: 			return KEYCODE_KEY_F18;
		case GLFW_KEY_F19: 			return KEYCODE_KEY_F19;
		case GLFW_KEY_F20: 			return KEYCODE_KEY_F20;
		case GLFW_KEY_F21: 			return KEYCODE_KEY_F21;
		case GLFW_KEY_F22: 			return KEYCODE_KEY_F22;
		case GLFW_KEY_F23: 			return KEYCODE_KEY_F23;
		case GLFW_KEY_F24: 			return KEYCODE_KEY_F24;
		case GLFW_KEY_F25: 			return KEYCODE_KEY_F25;
		case GLFW_KEY_KP_0: 		return KEYCODE_KEY_KP_0;
		case GLFW_KEY_KP_1: 		return KEYCODE_KEY_KP_1;
		case GLFW_KEY_KP_2: 		return KEYCODE_KEY_KP_2;
		case GLFW_KEY_KP_3: 		return KEYCODE_KEY_KP_3;
		case GLFW_KEY_KP_4: 		return KEYCODE_KEY_KP_4;
		case GLFW_KEY_KP_5: 		return KEYCODE_KEY_KP_5;
		case GLFW_KEY_KP_6: 		return KEYCODE_KEY_KP_6;
		case GLFW_KEY_KP_7: 		return KEYCODE_KEY_KP_7;
		case GLFW_KEY_KP_8: 		return KEYCODE_KEY_KP_8;
		case GLFW_KEY_KP_9: 		return KEYCODE_KEY_KP_9;
		case GLFW_KEY_KP_DECIMAL: 	return KEYCODE_KEY_KP_DECIMAL;
		case GLFW_KEY_KP_DIVIDE: 	return KEYCODE_KEY_KP_DIVIDE;
		case GLFW_KEY_KP_MULTIPLY: 	return KEYCODE_KEY_KP_MULTIPLY;
		case GLFW_KEY_KP_SUBTRACT: 	return KEYCODE_KEY_KP_SUBTRACT;
		case GLFW_KEY_KP_ADD: 		return KEYCODE_KEY_KP_ADD;
		case GLFW_KEY_KP_ENTER: 	return KEYCODE_KEY_KP_ENTER;
		case GLFW_KEY_KP_EQUAL: 	return KEYCODE_KEY_KP_EQUAL;
		case GLFW_KEY_LEFT_SHIFT: 	return KEYCODE_KEY_LEFT_SHIFT;
		case GLFW_KEY_LEFT_CONTROL: return KEYCODE_KEY_LEFT_CONTROL;
		case GLFW_KEY_LEFT_ALT: 	return KEYCODE_KEY_LEFT_ALT;
		case GLFW_KEY_LEFT_SUPER: 	return KEYCODE_KEY_LEFT_SUPER;
		case GLFW_KEY_RIGHT_SHIFT: 	return KEYCODE_KEY_RIGHT_SHIFT;
		case GLFW_KEY_RIGHT_CONTROL:return KEYCODE_KEY_RIGHT_CONTROL;
		case GLFW_KEY_RIGHT_ALT: 	return KEYCODE_KEY_RIGHT_ALT;
		case GLFW_KEY_RIGHT_SUPER: 	return KEYCODE_KEY_RIGHT_SUPER;
		case GLFW_KEY_MENU: 		return KEYCODE_KEY_MENU;
		default:					return KEYCODE_KEY_UNKNOWN;
	}
}

#endif