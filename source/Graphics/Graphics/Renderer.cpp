#include "Renderer.h"

#include "Shaders/Shader3d.h"
#include "Shaders/SimpleShader3d.h"
#include "Shaders/SkyboxShader.h"
#include "Shaders/ShadowShader.h"
#include "Shaders/HdrShader.h"
#include "Shaders/OutlineAddShader.h"
#include "Shaders/AddShader.h"

#include "RenderTexture.h"
#include "BloomEffectRenderer.h"
#include "BlurEffectRenderer.h"
#include "Shaders/BypassPostprocessingShader.h"
#include <vector>
#include <algorithm>
#include <iostream>


enum class RenderObjectsType
{
	Normal,
	Shadows,
	Outline
};

struct RendererImpl
{
	static const int MAX_LIGHTS_WITH_SHADOWS = 4;
	static const int MAX_LIGHTS_WITHOUT_SHADOWS = 16;

	RenderTarget& baseRenderTarget;

	Camera camera;
	RendererSettings settings;
	std::vector<std::shared_ptr<RenderObject>> renderObjects;
	std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
	std::vector<std::shared_ptr<PositionalLight>> positionalLights;

	Shader3d shader;
	SimpleShader3d simpleShader3d;
	BypassPostprocessingShader bypassPPShader;
	SkyboxShader skyboxShader;
	HdrShader hdrShader;
	ShadowShader shadowShader;
	AddShader addShader;
	OutlineAddShader outlineAddShader;

	std::shared_ptr<BloomEffectRenderer> bloomEffectRenderer;

	std::shared_ptr<RenderTexture> renderTexture;
	std::shared_ptr<RenderTexture> renderTexture2;
	std::shared_ptr<RenderTexture> renderTexture3;

	std::shared_ptr<RenderTexture> textureForOutline;
	std::shared_ptr<RenderTexture> textureForOutline2;
	std::shared_ptr<RenderTexture> textureForOutline3;
	std::shared_ptr<BlurEffectRenderer> outlineBlurRenderer;
	Mesh screenMesh;

	std::shared_ptr<SkyboxObject> skybox;
	std::shared_ptr<RenderTexture> dirLightDepthTextures[MAX_LIGHTS_WITH_SHADOWS];

	RendererImpl(RenderTarget& baseRenderTarget) :
		baseRenderTarget(baseRenderTarget),
		screenMesh(GeometryDefinition::SCREEN),
		skybox(nullptr)
	{
		renderTexture = std::make_shared<RenderTexture>(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Float, true);
		renderTexture2 = std::make_shared<RenderTexture>(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Float, true);
		renderTexture3 = std::make_shared<RenderTexture>(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Float, true);
		textureForOutline = std::make_shared<RenderTexture>(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Integer, true);
		textureForOutline2 = std::make_shared<RenderTexture>(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Integer, true);
		textureForOutline3 = std::make_shared<RenderTexture>(baseRenderTarget.getWidth(), baseRenderTarget.getHeight(), RenderTextureType::Integer, true);

		if (!renderTexture->init() || !renderTexture2->init() || !renderTexture3->init() || 
			!textureForOutline->init() || !textureForOutline2->init() || !textureForOutline3->init())
		{
			std::cout << "failed to create render texture inside of Renderer" << std::endl;
		}

		bloomEffectRenderer = std::make_shared<BloomEffectRenderer>(*renderTexture2, *renderTexture3);
		outlineBlurRenderer = std::make_shared<BlurEffectRenderer>(*textureForOutline3, 10.0f);
		outlineBlurRenderer->setNumberOfPasses(3);

		for (int i = 0; i < MAX_LIGHTS_WITH_SHADOWS; i++)
		{
			dirLightDepthTextures[i] = std::make_shared<RenderTexture>
				(2048, 2048, RenderTextureType::IntegerDepth, false);
			if (!dirLightDepthTextures[i]->init())
			{
				std::cout << "failed to create depth texture inside of Renderer" << std::endl;
			}
		}
	}

	void renderObject(RenderObject& obj);
	void renderObjectShadow(RenderObject& obj);
	void renderObjectOutline(RenderObject& obj);
	void renderGameObjects(RenderObjectsType renderType, const Camera& camera);
};

Renderer::Renderer(RenderTarget& baseRenderTarget)
{
	data = std::make_shared<RendererImpl>(baseRenderTarget);
}

void Renderer::updateRenderTargetSize(int width, int height)
{
	data->renderTexture = std::make_shared<RenderTexture>(width, height, RenderTextureType::Float, true);
	data->renderTexture2 = std::make_shared <RenderTexture>(width, height, RenderTextureType::Float, true);
	if (!data->renderTexture->init() || !data->renderTexture->init())
	{
		std::cout << "failed to re-init render textures after resize" << std::endl;
	}
}

Camera& Renderer::getCamera()
{
	return data->camera;
}

RendererSettings& Renderer::getSettings()
{
	return data->settings;
}

void RendererImpl::renderObjectShadow(RenderObject& obj)
{
	shadowShader.setModelMatrix(obj.transform.getWorldMatrix());
	obj.mesh.draw();
}

void RendererImpl::renderObject(RenderObject& obj)
{
	shader.setModelMatrix(obj.transform.getWorldMatrix());
	glm::mat4x4 modelViewMatrix = camera.getViewMatrix() * obj.transform.getWorldMatrix();
	shader.setNormalMatrix(glm::transpose(glm::inverse(modelViewMatrix)));
	shader.setMaterial(obj.material, 0);
	shader.setDiffuseTexture(obj.getDiffuseTexture());
	if (obj.hasNormalTexture)
	{
		shader.setNormalMapEnabled(true);
		shader.setNormalTexture(obj.getNormalTexture());
	}
	else
	{
		shader.setNormalMapEnabled(false);
	}
	if (obj.textureScalingEnabled)
	{
		shader.setTextureScalingEnabled(true);
		shader.setTextureScale(obj.transform.scale * obj.textureScaleMultiplier);
	}
	else
	{
		shader.setTextureScalingEnabled(false);
	}

	obj.mesh.draw();
}



void RendererImpl::renderObjectOutline(RenderObject& obj)
{
	simpleShader3d.setModelMatrix(obj.transform.getWorldMatrix());
	glm::mat4x4 modelViewMatrix = camera.getViewMatrix() * obj.transform.getWorldMatrix();
	simpleShader3d.setNormalMatrix(glm::transpose(glm::inverse(modelViewMatrix)));
	
	if (obj.hasOutline)
	{
		simpleShader3d.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		simpleShader3d.setColor(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	//simpleShader3d.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	obj.mesh.draw();
}

void RendererImpl::renderGameObjects(RenderObjectsType renderType, const Camera& camera)
{
	static const float eps = 0.00001f;
	std::vector<std::shared_ptr<RenderObject>> opaqueObjects;
	std::vector<std::shared_ptr<RenderObject>> transparentObjects;
	for (const auto& renderObject : renderObjects)
	{
		if (abs(renderObject->material.alpha - 1.0f) < eps)
		{
			if (renderType != RenderObjectsType::Shadows || renderObject->castsShadows)
			{
				opaqueObjects.push_back(renderObject);
			}
		}
		else
		{
			if (renderType != RenderObjectsType::Shadows)
			{
				transparentObjects.push_back(renderObject);
			}
		}
	}

	std::sort(opaqueObjects.begin(), opaqueObjects.end(), [&camera](const auto& obj1, const auto obj2)
		{
			float distance1 = glm::distance(obj1->transform.position, camera.position);
			float distance2 = glm::distance(obj2->transform.position, camera.position);
			return distance1 < distance2;
		});

	std::sort(transparentObjects.begin(), transparentObjects.end(), [&camera](const auto& obj1, const auto obj2)
	{
		float distance1 = glm::distance(obj1->transform.position, camera.position);
		float distance2 = glm::distance(obj2->transform.position, camera.position);
		return distance1 > distance2;
	});

	//rendering opaque objects first

	for (const auto& obj : opaqueObjects)
	{
		switch (renderType)
		{
		case RenderObjectsType::Normal:
			renderObject(*obj);
			break;
		case RenderObjectsType::Shadows:
			renderObjectShadow(*obj);
			break;
		case RenderObjectsType::Outline:
			renderObjectOutline(*obj);
			break;
		}
	}

	//rendering semi-transparent objects

	if (renderType != RenderObjectsType::Shadows)
	{
		for (const auto& obj : transparentObjects)
		{
			switch (renderType)
			{
			case RenderObjectsType::Normal:
				renderObject(*obj);
				break;
			case RenderObjectsType::Outline:
				renderObjectOutline(*obj);
				break;
			}
		}
	}
}

void Renderer::renderScene()
{
	//rendering depth textures
	std::vector<std::shared_ptr<DirectionalLight>> lightsWithShadows;
	std::vector<std::shared_ptr<DirectionalLight>> lightsWithoutShadows;
	std::vector<Camera> lightCameras;
	for (const auto& dirLight : data->directionalLights)
	{
		if (dirLight->shadowsEnabled)
		{
			lightsWithShadows.push_back(dirLight);
		}
		else
		{
			lightsWithoutShadows.push_back(dirLight);
		}
	}
	if (lightsWithShadows.size() > RendererImpl::MAX_LIGHTS_WITH_SHADOWS)
	{
		std::cout << "error! too much directional lights with shadows: " << lightsWithShadows.size() << std::endl;
	}

	for (int i = 0; i < lightsWithShadows.size(); i++)
	{
		data->dirLightDepthTextures[i]->bind();
		data->dirLightDepthTextures[i]->clear();
		data->shadowShader.bind();
		
		//Camera dirLightCamera = data->camera.getDirectionalLightCamera(-lightsWithShadows[i]->direction, 100.0f);
		//dirLightCamera.setOrtho(-50, 50, -50, 50, -50, 50);
		//dirLightCamera.position = glm::vec3(0, 0, 0);
		//lightCameras.push_back(dirLightCamera);
		lightCameras.push_back(data->camera.getDirectionalLightCamera(-lightsWithShadows[i]->direction, 12.0f));
		data->shadowShader.setViewMatrix(lightCameras.back().getViewMatrix());
		data->shadowShader.setProjectionMatrix(lightCameras.back().getProjectionMatrix());
		data->renderGameObjects(RenderObjectsType::Shadows, lightCameras.back());
	}

	//bind render texture

	data->renderTexture->bind();
	data->renderTexture->clear();
	
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

	data->shader.setDirectionalLightsWithShadowsCount(lightsWithShadows.size());
	for (int i = 0; i < lightsWithShadows.size(); i++)
	{
		data->shader.setDirectionalLightWithShadow(*lightsWithShadows[i], data->camera.getViewMatrix(), data->dirLightDepthTextures[i]->getRenderedTexture(), i);
		data->shader.setShadowDirLightViewProjection(lightCameras[i].getProjectionMatrix() * lightCameras[i].getViewMatrix(), i);
	}

	if (data->skybox != nullptr)
	{
		data->shader.setEnvironmentMap(data->skybox->cubemap);
		data->shader.setEnvironmentMapEnabled(true);
	}
	else
	{
		data->shader.setEnvironmentMapEnabled(false);
	}

	//setting lights to uniforms

	data->shader.setDirectionalLightsCount(lightsWithoutShadows.size());
	for (int i = 0; i < lightsWithoutShadows.size(); i++)
	{
		data->shader.setDirectionalLight(*lightsWithoutShadows[i], data->camera.getViewMatrix(), i);
	}

	data->shader.setPositionalLightsCount(data->positionalLights.size());
	for (int i = 0; i < data->positionalLights.size(); i++)
	{
		data->shader.setPositionalLight(*data->positionalLights[i], i);
	}

	data->renderGameObjects(RenderObjectsType::Normal, data->camera);
	data->renderTexture->updateTexture(false);

	//applying bloom
	if (data->settings.bloomEnabled)
	{
		data->bloomEffectRenderer->setBrightnessThreshold(data->settings.bloomThreshold);
		data->bloomEffectRenderer->render(*data->renderTexture);
	}

	//preparing outline textures

	data->textureForOutline->bind();
	data->textureForOutline->setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	data->textureForOutline->clear();

	data->simpleShader3d.bind();
	data->simpleShader3d.setProjectionMatrix(data->camera.getProjectionMatrix());
	data->simpleShader3d.setViewMatrix(data->camera.getViewMatrix());
	data->simpleShader3d.setEyeDirection(data->camera.dirFront);

	data->renderGameObjects(RenderObjectsType::Outline, data->camera);
	data->textureForOutline->updateTexture(false);

	data->textureForOutline2->bind();
	data->textureForOutline2->setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	data->textureForOutline2->clear();
	data->bypassPPShader.bind();
	data->bypassPPShader.setScreenTexture(data->textureForOutline->getRenderedTexture());
	data->screenMesh.draw();
	data->textureForOutline2->updateTexture(false);
	
	data->outlineBlurRenderer->render(*data->textureForOutline2);
	
	data->textureForOutline3->bind();
	data->textureForOutline3->setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	data->textureForOutline3->clear();
	data->addShader.bind();
	data->addShader.setMultiplier1(2.0f);
	data->addShader.setMultiplier2(-2.0f);
	data->addShader.setTexture1(data->textureForOutline2->getRenderedTexture()); //blurred
	data->addShader.setTexture2(data->textureForOutline->getRenderedTexture());
	data->screenMesh.draw();
	data->textureForOutline3->updateTexture(false);

	//mixing outline with rendered scene

	data->textureForOutline2->bind();
	data->textureForOutline2->clear();

	data->hdrShader.bind();
	if (data->settings.bloomEnabled)
	{
		data->hdrShader.setScreenTexture(data->bloomEffectRenderer->getOutputTexture().getRenderedTexture());
	}
	else
	{
		data->hdrShader.setScreenTexture(data->renderTexture->getRenderedTexture());
	}
	data->hdrShader.setToneMappingEnabled(data->settings.toneMappingEnabled);
	data->hdrShader.setGammaCorrectionEnabled(data->settings.gammaCorrectionEnabled);
	data->hdrShader.setGamma(data->settings.gamma);
	data->hdrShader.setContrast(data->settings.contrast);
	data->hdrShader.setExposure(data->settings.exposure);
	data->screenMesh.draw();
	data->textureForOutline2->updateTexture(false);
	
	data->baseRenderTarget.bind();
	
	data->outlineAddShader.bind();
	data->outlineAddShader.setOutlineColor(glm::vec3(1.0f, 0.5f, 0.0f));
	data->outlineAddShader.setOutlineTexture(data->textureForOutline3->getRenderedTexture());
	data->outlineAddShader.setScreenTexture(data->textureForOutline2->getRenderedTexture());
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

int Renderer::getMaxLightsWithShadows()
{
	return RendererImpl::MAX_LIGHTS_WITH_SHADOWS;
}

int Renderer::getMaxLightsWithoutShadows()
{
	return RendererImpl::MAX_LIGHTS_WITHOUT_SHADOWS;
}

bool Renderer::isValid()
{
	int dirLightsWithShadows = 0;
	int dirLightsWithoutShadows = 0;
	int pointLightsWithShadows = 0;
	int pointLightsWithoutShadows = 0;

	for (const auto& dirLight : data->directionalLights)
	{
		if (dirLight->shadowsEnabled)
		{
			dirLightsWithShadows++;
		}
		else
		{
			dirLightsWithoutShadows++;
		}
	}

	for (const auto& pointLight : data->positionalLights)
	{
		if (pointLight->shadowsEnabled)
		{
			pointLightsWithShadows++;
		}
		else
		{
			pointLightsWithoutShadows++;
		}
	}

	if (dirLightsWithShadows > RendererImpl::MAX_LIGHTS_WITH_SHADOWS) return false;
	if (dirLightsWithoutShadows > RendererImpl::MAX_LIGHTS_WITHOUT_SHADOWS) return false;
	if (pointLightsWithShadows > RendererImpl::MAX_LIGHTS_WITH_SHADOWS) return false;
	if (pointLightsWithoutShadows > RendererImpl::MAX_LIGHTS_WITHOUT_SHADOWS) return false;
	
	return true;
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