#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include <memory>
#include <Graphics/RenderTarget.h>

struct LevelEditorImpl;

struct LevelEditor
{
	LevelEditor(RenderTarget& renderWindow);
	~LevelEditor();

	void render(RenderTarget& renderTarget, float dt);

private:
	std::unique_ptr<LevelEditorImpl> data;
};


#endif