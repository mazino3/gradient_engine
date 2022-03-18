#include "Resources.h"
#include <unordered_map>

struct ResourcesImpl
{
	std::shared_ptr<Texture> whiteTexture;
	std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
};

Resources::Resources()
{
	data = std::make_unique<ResourcesImpl>();
	data->whiteTexture = std::make_shared<Texture>(Texture::createWhiteTexture());
}

Resources::~Resources()
{
}

std::weak_ptr<Texture> Resources::getWhiteTexture()
{
	return data->whiteTexture;
}

std::weak_ptr<Texture> Resources::getTexture(const std::string& filename)
{
	if (data->loadedTextures.find(filename) == data->loadedTextures.end())
	{
		data->loadedTextures[filename] = std::make_shared<Texture>(filename);
	}
	return data->loadedTextures[filename];
}
