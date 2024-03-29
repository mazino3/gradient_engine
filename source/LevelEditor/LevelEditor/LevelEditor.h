#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include <memory>
#include <vector>
#include <utility>
#include <Graphics/RenderTarget.h>
#include <Graphics/InputClient.h>

struct LevelEditorImpl;

struct LevelEditor
{
	LevelEditor(RenderTarget& renderWindow);
	~LevelEditor();

	void render(RenderTarget& renderTarget, float dt);
	std::vector<std::pair<float, InputClientBase*>> getInputClients();

private:
	std::unique_ptr<LevelEditorImpl> data;
};


#endif