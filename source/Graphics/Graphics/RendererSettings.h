#ifndef GRAPHICS_RENDERER_SETTINGS_H
#define GRAPHICS_RENDERER_SETTINGS_H

#include <glm/vec3.hpp>

struct RendererSettings
{
	bool toneMappingEnabled;
	bool gammaCorrectionEnabled;
	float gamma;
	float contrast;
	float exposure;

	bool bloomEnabled;
	float bloomThreshold;

	glm::vec3 fogColor;
	glm::vec3 outlineColor;
	float fogDistance;
	float fogPower;

	RendererSettings() :
		toneMappingEnabled(true),
		gammaCorrectionEnabled(true),
		gamma(2.2f),
		contrast(0.4f),
		exposure(2.0f),
		bloomEnabled(true),
		bloomThreshold(0.7f),
		fogColor(1, 1, 1),
		outlineColor(1.0f, 0.5f, 0.0f),
		fogDistance(50.0f),
		fogPower(5.0f)
	{}
};

#endif