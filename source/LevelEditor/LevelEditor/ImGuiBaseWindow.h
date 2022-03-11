#ifndef IMGUI_BASE_WINDOW_H
#define IMGUI_BASE_WINDOW_H

#include <memory>
#include <string>
#include <functional>
#include <glm/vec2.hpp>
#include <imgui.h>

struct ImGuiBaseWindowImpl;
struct ImGuiButtonHandlerImpl;

struct ImGuiButtonHandler
{
	ImGuiButtonHandler();
	~ImGuiButtonHandler();

	void onButtonPressed(std::function<void(void)> callback);
	void fireOnButtonPressed();

private:
	std::unique_ptr<ImGuiButtonHandlerImpl> data;
	friend class ImGuiBaseWindow;
};

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

	ImGuiButtonHandler& createButton(float x, float y, const std::string& name);

	void render();

private:
	std::unique_ptr<ImGuiBaseWindowImpl> data;
};

#endif