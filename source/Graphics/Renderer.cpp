#include "Renderer.h"
#include "Shader3d.h"
#include "SkyboxShader.h"
#include "HdrShader.h"
#include "RenderTexture.h"
#include <vector>
#include <algorithm>
#include <iostream>

struct RendererImpl
{
	RenderTarget& baseRenderTarget;

	Camera camera;
	std::vector<std::shared_ptr<RenderObject>> renderObjects;
	std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
	std::vector<std::shared_ptr<PositionalLight>> positionalLights;
	Shader3d shader;
	SkyboxShader skyboxShader;
	HdrShader hdrShader;

	RenderTexture renderTexture;
	Mesh screenMesh;

	std::shared_ptr<SkyboxObject> skybox;

	RendererImpl(RenderTarget& baseRenderTarget) :
		baseRenderTarget(baseRenderTarget),
		renderTexture(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Float, true),
		screenMesh(GeometryDefinition::SCREEN)
	{
		if (!renderTexture.init())
		{
			std::cout << "failed to create render texture inside of Renderer" << std::endl;
		}
	}

	void renderObject(std::shared_ptr<RenderObject> obj)
	{
		shader.setModelMatrix(obj->transform.getWorldMatrix());
		glm::mat4x4 modelViewMatrix = camera.getViewMatrix() * obj->transform.getWorldMatrix();
		shader.setNormalMatrix(glm::transpose(glm::inverse(modelViewMatrix)));
		shader.setMaterial(obj->material, 0);
		shader.setDiffuseTexture(obj->getDiffuseTexture());
		if (obj->hasNormalTexture)
		{
			shader.setNormalMapEnabled(true);
			shader.setNormalTexture(obj->getNormalTexture());
		}
		else
		{
			shader.setNormalMapEnabled(false);
		}

		obj->mesh.draw();
	}
};

Renderer::Renderer(RenderTarget& baseRenderTarget)
{
	data = std::make_shared<RendererImpl>(baseRenderTarget);
}

Camera& Renderer::getCamera()
{
	return data->camera;
}

void Renderer::renderScene()
{
	static const float eps = 0.00001f;
	std::vector<std::shared_ptr<RenderObject>> opaqueObjects;
	std::vector<std::shared_ptr<RenderObject>> transparentObjects;
	for (const auto& renderObject : data->renderObjects)
	{
		if (abs(renderObject->material.alpha - 1.0f) < eps)
		{
			opaqueObjects.push_back(renderObject);
		}
		else
		{
			transparentObjects.push_back(renderObject);
		}
	}
	
	//sorting opaque objects by distance to the camera (from near to far)

	std::sort(opaqueObjects.begin(), opaqueObjects.end(), [this](const auto& obj1, const auto obj2) 
	{
		float distance1 = glm::distance(obj1->transform.position, data->camera.position);
		float distance2 = glm::distance(obj2->transform.position, data->camera.position);
		return distance1 < distance2;
	});

	//sorting transparent objects by distance to the camera (from far to near)

	std::sort(transparentObjects.begin(), transparentObjects.end(), [this](const auto& obj1, const auto obj2)
	{
		float distance1 = glm::distance(obj1->transform.position, data->camera.position);
		float distance2 = glm::distance(obj2->transform.position, data->camera.position);
		return distance1 > distance2;
	});

	//bind render texture

	data->renderTexture.bind();
	data->renderTexture.clear();

	if (data->skybox != nullptr)
	{
		data->skyboxShader.bind();
		data->skyboxShader.setProjectionMatrix(data->camera.getProjectionMatrix());
		data->skyboxShader.setViewMatrix(glm::mat4(glm::mat3(data->camera.getViewMatrix())));
		data->skyboxShader.setModelMatrix(data->skybox->transform.getWorldMatrix());
		data->skyboxShader.setSkyboxCubemap(data->skybox->cubemap);
		data->skybox->mesh.draw();
	}

	data->shader.bind();
	data->shader.setProjectionMatrix(data->camera.getProjectionMatrix());
	data->shader.setViewMatrix(data->camera.getViewMatrix());
	data->shader.setCurrentMaterialIndex(0); //todo: group objects by materials
	data->shader.setEyeDirection(data->camera.dirFront);
	data->shader.setEnvironmentMap(data->skybox->cubemap);

	//setting lights to uniforms

	data->shader.setDirectionalLightsCount(data->directionalLights.size());
	for (int i = 0; i < data->directionalLights.size(); i++)
	{
		data->shader.setDirectionalLight(*data->directionalLights[i], i);
	}

	data->shader.setPositionalLightsCount(data->positionalLights.size());
	for (int i = 0; i < data->positionalLights.size(); i++)
	{
		data->shader.setPositionalLight(*data->positionalLights[i], i);
	}

	//rendering opaque objects first

	for (const auto& obj : opaqueObjects)
	{
		data->renderObject(obj);
	}

	//rendering semi-transparent objects

	for (const auto& obj : transparentObjects)
	{
		data->renderObject(obj);
	}

	data->renderTexture.updateTexture(false);

	//binding base render target and applying post-processing

	data->baseRenderTarget.bind();
	data->hdrShader.bind();
	data->hdrShader.setScreenTexture(data->renderTexture.getRenderedTexture());
	data->hdrShader.setToneMappingEnabled(true);
	data->hdrShader.setGammaCorrectionEnabled(true);
	data->hdrShader.setGamma(2.2f);
	data->hdrShader.setContrast(0.4f);
	data->hdrShader.setExposure(2.0f);
	data->screenMesh.draw();
}

RenderObject& Renderer::createRenderObject(Texture& diffuseTexture, const GeometryDefinition& geometryDefinition, const Material& material)
{
	auto result = std::make_shared<RenderObject>(diffuseTexture, geometryDefinition, material);
	data->renderObjects.push_back(result);
	return *result;
}

RenderObject& Renderer::createRenderObject(Texture& diffuseTexture, Texture& normalTexture, const GeometryDefinition& geometryDefinition, const Material& material)
{
	auto result = std::make_shared<RenderObject>(diffuseTexture, normalTexture, geometryDefinition, material);
	data->renderObjects.push_back(result);
	return *result;
}

void Renderer::removeRenderObject(RenderObject& objectToRemove)
{
	std::remove_if(data->renderObjects.begin(), data->renderObjects.end(), [&](const auto& renderObject) 
	{
		return &(*renderObject) == &objectToRemove;
	});
}

void Renderer::createSkybox(CubeMap& cubemap)
{
	removeSkybox();
	data->skybox = std::make_shared<SkyboxObject>(cubemap);
}

void Renderer::removeSkybox()
{
	data->skybox = nullptr;
}

DirectionalLight& Renderer::createDirectionalLight()
{
	auto result = std::make_shared<DirectionalLight>();
	data->directionalLights.push_back(result);
	return *result;
}

void Renderer::removeDirectionalLight(DirectionalLight& lightToRemove)
{
	std::remove_if(data->directionalLights.begin(), data->directionalLights.end(), [&](const auto& light) 
	{
		return &(*light) == &lightToRemove;
	});
}

PositionalLight& Renderer::createPositionalLight()
{
	auto result = std::make_shared<PositionalLight>();
	data->positionalLights.push_back(result);
	return *result;
}

void Renderer::removePositionalLight(PositionalLight& lightToRemove)
{
	std::remove_if(data->positionalLights.begin(), data->positionalLights.end(), [&](const auto& light) 
	{
		return &(*light) == &lightToRemove;
	});
}