#include <vector>
#include <LevelEditor/ImGuiBaseWindow.h>

struct ImGuiButtonHandlerImpl
{
	std::function<void(void)> callback;
	std::string name;
	glm::vec2 pos;

	ImGuiButtonHandlerImpl() :
		callback([](){}),
		pos(0, 0)
	{}
};

struct ImGuiBaseWindowImpl
{
	glm::vec2 size;
	glm::vec2 pos;
	std::string windowName;
	std::vector<std::shared_ptr<ImGuiButtonHandler>> buttonHandlers;

	ImGuiBaseWindowImpl();
};

ImGuiButtonHandler::ImGuiButtonHandler()
{
	data = std::make_unique<ImGuiButtonHandlerImpl>();
}

ImGuiButtonHandler::~ImGuiButtonHandler()
{
}

void ImGuiButtonHandler::onButtonPressed(std::function<void(void)> callback)
{
	data->callback = callback;
}

void ImGuiButtonHandler::fireOnButtonPressed()
{
	data->callback();
}

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

	for (auto& handler : data->buttonHandlers)
	{
		auto prevCur = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(handler->data->pos.x, handler->data->pos.y));
		if (ImGui::Button(handler->data->name.c_str()))
		{
			handler->fireOnButtonPressed();
		}
	}

	ImGui::End();
}

ImGuiButtonHandler& ImGuiBaseWindow::createButton(float x, float y, const std::string& name)
{
	auto handler = std::make_shared<ImGuiButtonHandler>();
	data->buttonHandlers.push_back(handler);
	handler->data->name = name;
	handler->data->pos = glm::vec2(x, y);

	return *handler;
}