#ifndef GRAPHICS_CUBEMAP_H
#define GRAPHICS_CUBEMAP_H

#include <memory>
#include <vector>
#include <string>

struct CubeMapImpl;

struct CubeMap
{
	CubeMap(std::vector<std::string> images);
	~CubeMap();
	void bind();
	void bind(int unit);

private:
	std::shared_ptr<CubeMapImpl> data;
};

#endif