#ifndef IMGUI_BASE_WINDOW_H
#define IMGUI_BASE_WINDOW_H

#include <memory>
#include <string>
#include <glm/vec2.hpp>
#include <imgui.h>

struct ImGuiBaseWindowImpl;

struct ImGuiBaseWindow
{
	ImGuiWindowFlags windowFlags;

	ImGuiBaseWindow();
	~ImGuiBaseWindow();

	void setSize(float x, float y);
	glm::vec2 getSize();

	void setPos(float x, float y);
	glm::vec2 getPos();

	void setName(const std::string& windowName);
	std::string getName();

	void render();

private:
	std::unique_ptr<ImGuiBaseWindowImpl> data;
};

#endif