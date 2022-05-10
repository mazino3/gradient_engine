#include "ResizeManager.h"

struct ResizeManagerImpl
{
	//todo: implement
	InputClient inputClient;
};

ResizeManager::ResizeManager()
{
	data = std::make_unique<ResizeManagerImpl>();
}

ResizeManager::~ResizeManager()
{
}

InputClient& ResizeManager::getInputClient()
{
	return data->inputClient;
}

void ResizeManager::startDragging(LevelObject& levelObject, ArrowType arrowType, Plane arrowPlane)
{
	//todo: implement
}