#ifndef GRAPHICS_RENDERER_SETTINGS_H
#define GRAPHICS_RENDERER_SETTINGS_H

struct RendererSettings
{
	bool toneMappingEnabled;
	bool gammaCorrectionEnabled;
	float gamma;
	float contrast;
	float exposure;

	RendererSettings() :
		toneMappingEnabled(true),
		gammaCorrectionEnabled(true),
		gamma(2.2f),
		contrast(0.4f),
		exposure(2.0f) 
	{}
};

#endif