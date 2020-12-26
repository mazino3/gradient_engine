#include "Lights.h"

DirectionalLight::DirectionalLight() :
	ambientColor(0, 0, 0),
	diffuseColor(0, 0, 0),
	specularColor(0, 0, 0),
	direction(0, 0, 0),
	shadowsEnabled(false)
{}

PositionalLight::PositionalLight() :
	ambientColor(0, 0, 0),
	diffuseColor(0, 0, 0),
	specularColor(0, 0, 0),
	position(0, 0, 0),
	constantAttenuation(0.0f),
	linearAttenuation(0.0f),
	quadraticAttenuation(0.0f)
{}