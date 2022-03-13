#include <LevelEditor/LevelObject.h>

struct LevelObjectImpl
{
	RenderObject* renderObject;

	LevelObjectImpl(Renderer& renderer);
	~LevelObjectImpl();
};

LevelObjectImpl::LevelObjectImpl(Renderer& renderer)
{
	//todo: create render object	
}

LevelObjectImpl::~LevelObjectImpl()
{
	//todo: delete render object
}

LevelObject::LevelObject(Renderer& renderer, glm::vec3 pos, glm::vec3 scale)
{
	data = std::make_unique<LevelObjectImpl>(renderer);
}

LevelObject::~LevelObject()
{

}