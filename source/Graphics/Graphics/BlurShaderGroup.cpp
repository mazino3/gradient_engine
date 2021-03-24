#include <Graphics/BlurShaderGroup.h>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

struct BlurShaderData
{
	std::shared_ptr<BlurShader> shader;
	float radius;

	BlurShaderData() :
		radius(0.0f)
	{}

	BlurShaderData(std::shared_ptr<BlurShader> shader, float radius) :
		shader(shader),
		radius(radius)
	{}
};

struct BlurShaderGroupImpl
{
	float radius;
	std::vector<BlurShaderData> blurShaders;
};

BlurShaderGroup::BlurShaderGroup(float minRadius, float maxRadius, float step)
{
	data = std::make_shared<BlurShaderGroupImpl>();
	data->radius = minRadius;
	
	if (minRadius > maxRadius)
	{
		std::swap(minRadius, maxRadius);
	}
	step = std::abs(step);
	if (step < 0.001f)
	{
		std::cout << "error! step is too low in BlurShaderGroup: " << step << std::endl;
	}

	float currentRadius = minRadius;
	while (currentRadius <= maxRadius)
	{
		auto shader = std::make_shared<BlurShader>(currentRadius);
		data->blurShaders.push_back(BlurShaderData(shader, currentRadius));
		currentRadius += step;
	}
}

void BlurShaderGroup::setRadius(float radius)
{
	data->radius = radius;
}

void BlurShaderGroup::bind(Texture& screenTexture, float pixelSize, bool isHorizontal)
{
	if (data->blurShaders.size() == 0)
	{
		std::cout << "no shaders to bind in BlurShaderGroup" << std::endl;
		return; //we have no shader to bind
	}
	BlurShaderData currentShaderData = data->blurShaders.front();
	for (const auto& shaderData : data->blurShaders)
	{
		float currentDistance = std::abs(currentShaderData.radius - data->radius);
		float distance = std::abs(shaderData.radius - data->radius);
		if (distance < currentDistance)
		{
			currentShaderData = shaderData;
		}
	}
	currentShaderData.shader->bind();

	auto shader = currentShaderData.shader;
	shader->setScreenTexture(screenTexture);
	shader->setPixelSize(pixelSize);
	shader->setHorizontal(isHorizontal);
}

