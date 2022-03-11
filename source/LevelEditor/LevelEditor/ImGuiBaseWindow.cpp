#include <LevelEditor/ImGuiBaseWindow.h>

struct ImGuiBaseWindowImpl
{
	glm::vec2 size;
	glm::vec2 pos;
	std::string windowName;

	ImGuiBaseWindowImpl();
};

ImGuiBaseWindowImpl::ImGuiBaseWindowImpl() :
	size(0, 0),
	pos(0, 0)
{}

ImGuiBaseWindow::ImGuiBaseWindow() :
	windowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)
{
	data = std::make_unique<ImGuiBaseWindowImpl>();
}

ImGuiBaseWindow::~ImGuiBaseWindow()
{
}

void ImGuiBaseWindow::setSize(float x, float y)
{
	data->size.x = x;
	data->size.y = y;
}

glm::vec2 ImGuiBaseWindow::getSize()
{
	return data->size;
}

void ImGuiBaseWindow::setPos(float x, float y)
{
	data->pos.x = x;
	data->pos.y = y;
}

glm::vec2 ImGuiBaseWindow::getPos()
{
	return data->pos;
}

void ImGuiBaseWindow::setName(const std::string& windowName)
{
	data->windowName = windowName;
}

std::string ImGuiBaseWindow::getName()
{
	return data->windowName;
}

void ImGuiBaseWindow::render()
{
	ImGui::Begin(data->windowName.c_str(), nullptr, windowFlags);

	ImGui::SetWindowSize(ImVec2(data->size.x, data->size.y));
	ImGui::SetWindowPos(ImVec2(data->pos.x, data->pos.y));

	ImGui::End();
}