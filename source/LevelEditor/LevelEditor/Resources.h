#ifndef RESOURCES_H
#define RESOURCES_H

#include <memory>
#include <string>
#include <Graphics/Texture.h>

struct ResourcesImpl;

struct Resources
{
	Resources();
	~Resources();

	std::weak_ptr<Texture> getWhiteTexture();
	std::weak_ptr<Texture> getTexture(const std::string& filename);

private:
	std::unique_ptr<ResourcesImpl> data;
};

#endif