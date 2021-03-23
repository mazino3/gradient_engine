#ifndef GRAPHICS_RENDER_OBJECT_H
#define GRAPHICS_RENDER_OBJECT_H

#include "Texture.h"
#include "GeometryDefinition.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

struct RenderObject
{
	const bool hasNormalTexture;
	Mesh mesh;
	Transform transform;
	Material material;

	bool textureScalingEnabled;
	bool castsShadows;
	bool hasOutline;
	float textureScaleMultiplier;

	RenderObject(Texture& diffuseTexture, const GeometryDefinition& geometryDefinition, const Material& material) :
		diffuseTexture(&diffuseTexture),
		normalTexture(nullptr),
		hasNormalTexture(false),
		mesh(geometryDefinition),
		material(material),
		textureScalingEnabled(false),
		textureScaleMultiplier(1.0f),
		castsShadows(true),
		hasOutline(false)
	{}

	RenderObject(Texture& diffuseTexture, Texture& normalTexture, const GeometryDefinition& geometryDefinition, const Material& material) :
		diffuseTexture(&diffuseTexture),
		normalTexture(&normalTexture),
		hasNormalTexture(true),
		mesh(geometryDefinition),
		material(material),
		textureScalingEnabled(false),
		textureScaleMultiplier(1.0f),
		castsShadows(true),
		hasOutline(false)
	{}

	Texture& getDiffuseTexture()
	{
		return *diffuseTexture;
	}

	Texture& getNormalTexture()
	{
		return *normalTexture;
	}

private:

	Texture* diffuseTexture;
	Texture* normalTexture;
};

#endif