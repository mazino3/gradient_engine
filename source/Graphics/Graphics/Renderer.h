#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include <memory>
#include <Graphics/Camera.h>
#include <Graphics/RenderObject.h>
#include <Graphics/RenderTarget.h>
#include <Graphics/SkyboxObject.h>
#include <Graphics/Lights.h>
#include <Graphics/RendererSettings.h>

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

	std::weak_ptr<RenderObject> createRenderObject(Texture& diffuseTexture, const GeometryDefinition& geometryDefinition, const Material& material);
	std::weak_ptr<RenderObject> createRenderObject(Texture& diffuseTexture, Texture& normalTexture, const GeometryDefinition& geometryDefinition, const Material& material);
	void removeRenderObject(RenderObject& renderObject);

	void createSkybox(CubeMap& cubemap);
	void removeSkybox();

	void updateRenderTargetSize(int width, int height);

	DirectionalLight& createDirectionalLight();
	void removeDirectionalLight(DirectionalLight& light);
	PositionalLight& createPositionalLight();
	void removePositionalLight(PositionalLight& light);

private:
	std::shared_ptr<RendererImpl> data;
};

#endif