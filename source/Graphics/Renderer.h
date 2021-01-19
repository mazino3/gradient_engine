#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include <memory>
#include "Camera.h"
#include "RenderObject.h"
#include "RenderTarget.h"
#include "SkyboxObject.h"
#include "Lights.h"
#include "RendererSettings.h"

struct RendererImpl;

struct Renderer
{
	Renderer(RenderTarget& renderTarget);

	Camera& getCamera();
	RendererSettings& getSettings();

	void renderScene();

	int getMaxLightsWithShadows();
	int getMaxLightsWithoutShadows();

	bool isValid();

	RenderObject& createRenderObject(Texture& diffuseTexture, const GeometryDefinition& geometryDefinition, const Material& material);
	RenderObject& createRenderObject(Texture& diffuseTexture, Texture& normalTexture, const GeometryDefinition& geometryDefinition, const Material& material);
	void removeRenderObject(RenderObject& renderObject);

	void createSkybox(CubeMap& cubemap);
	void removeSkybox();

	DirectionalLight& createDirectionalLight();
	void removeDirectionalLight(DirectionalLight& light);
	PositionalLight& createPositionalLight();
	void removePositionalLight(PositionalLight& light);

private:
	std::shared_ptr<RendererImpl> data;
};

#endif