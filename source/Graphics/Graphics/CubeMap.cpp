#include "CubeMap.h"
#include <iostream>
#include <GL/glew.h>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


struct CubeMapImpl
{
	GLuint textureHandler;
};

CubeMap::CubeMap(std::vector<std::string> faces)
{
	if (faces.size() != 6)
	{
		std::cout << "Error initializing cubemap! you should provide exactly 6 images. Provided images: " << faces.size() << std::endl;
	}

	data = std::make_shared<CubeMapImpl>();
	glGenTextures(1, &data->textureHandler);
	glBindTexture(GL_TEXTURE_CUBE_MAP, data->textureHandler);
	
	int width;
	int height;
	int numComponents;

	for (int i = 0; i < faces.size(); i++)
	{
		unsigned char* image_data = stbi_load(faces[i].c_str(), &width, &height, &numComponents, 0);
		if (data != nullptr)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		}
		else
		{
			std::cout << "failed to load cubemap face: " << faces[i] << std::endl;
		}
		stbi_image_free(image_data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &data->textureHandler);
}

void CubeMap::bind()
{
	bind(0);
}

void CubeMap::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, data->textureHandler);
}