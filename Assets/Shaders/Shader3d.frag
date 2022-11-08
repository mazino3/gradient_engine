#version 130
precision highp float;

struct MaterialProperties {
	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	float alpha;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct PositionalLight {
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

uniform int directionalLightsCount;
uniform DirectionalLight directionalLights[16];

uniform int directionalLightsWithShadowsCount;
uniform DirectionalLight directionalLightsWithShadows[4];
uniform sampler2D depthTextures[4];
uniform mat4 shadowDirLightVP[4];

uniform int positionalLightsCount;
uniform PositionalLight positionalLights[16];

uniform int materialIndex;
uniform MaterialProperties materials[16];

uniform bool normalMapEnabled;
uniform vec3 eyeDirection;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;

uniform bool envMapEnabled;
uniform samplerCube envMap;

uniform float fogDistance;
uniform float fogPower;
uniform vec3 fogColor;

in vec4 ex_Color;
in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_Tangent;
in vec3 ex_Bitangent;
in vec3 ex_VertPos;
in vec3 ex_VertPosWorld;
out vec4 outColor;

void main(void) {
	vec3 resultColor = vec3(0.0, 0.0, 0.0);
	vec3 normal = ex_Normal;
	vec3 vertexNormal = ex_Normal;
	if (normalMapEnabled)
	{
		vec4 normalColor = texture(normalTex, ex_TexCoord);
		normal.x = (normalColor.x * 2.0) - 1.0;
		normal.y = (normalColor.y * 2.0) - 1.0;
		normal.z = (normalColor.z * 2.0) - 1.0;
		
		normal = ex_Tangent * normal.x + ex_Bitangent * normal.y + ex_Normal * normal.z;
		normal = normalize(normal);
	}
	vec3 eyeDir = normalize(-ex_VertPos);
	
	//directional lights
	for (int i = 0; i < directionalLightsCount; i++) {
		vec3 reflection = normalize(reflect(-directionalLights[i].direction, normal));
		float cosTheta = dot(directionalLights[i].direction, normal);
		float cosPhi = dot(eyeDir, reflection);
		vec3 diffuse = directionalLights[i].diffuseColor * materials[materialIndex].diffuse * max(cosTheta, 0.0);
		vec3 specular = directionalLights[i].specularColor * materials[materialIndex].specular * pow(max(cosPhi, 0.0), materials[materialIndex].shininess);
		vec3 ambient = directionalLights[i].ambientColor * materials[materialIndex].ambient;
		resultColor += diffuse + specular + ambient;
	}
	
	//directional lights with shadows
	for (int i = 0; i < directionalLightsWithShadowsCount; i++) {
		vec3 reflection = normalize(reflect(-directionalLightsWithShadows[i].direction, normal));
		float cosTheta = dot(directionalLightsWithShadows[i].direction, normal);
		float cosPhi = dot(eyeDir, reflection);
		vec3 diffuse = directionalLightsWithShadows[i].diffuseColor * materials[materialIndex].diffuse * max(cosTheta, 0.0);
		vec3 specular = directionalLightsWithShadows[i].specularColor * materials[materialIndex].specular * pow(max(cosPhi, 0.0), materials[materialIndex].shininess);
		vec3 ambient = directionalLightsWithShadows[i].ambientColor * materials[materialIndex].ambient;
		
		vec4 lightTexCoord4 = shadowDirLightVP[i] * vec4(ex_VertPosWorld, 1.0);
		vec3 lightTexCoord = lightTexCoord4.xyz / lightTexCoord4.w;
		lightTexCoord = lightTexCoord * 0.5 + 0.5;
		float closestDepth = texture(depthTextures[i], lightTexCoord.xy).r;
		float currentDepth = lightTexCoord.z;
		float shadow = 1;
		
		if (currentDepth <= 1.0 && lightTexCoord.x >= 0 && lightTexCoord.x <= 1.0 && lightTexCoord.y >= 0 && lightTexCoord.y <= 1.0)
		{
			shadow = currentDepth - 0.00025 >= closestDepth ? 0.0 : 1.0;
		}
		
		resultColor += (diffuse + specular) * shadow + ambient;
	}
	
	//positional lights
	for (int i = 0; i < positionalLightsCount; i++) {
		vec3 direction = -normalize(ex_VertPos - positionalLights[i].position);
		vec3 reflection = normalize(reflect(-direction, normal));
		float cosTheta = dot(direction, normal);
		float cosPhi = dot(eyeDir, reflection);
		vec3 diffuse = positionalLights[i].diffuseColor * materials[materialIndex].diffuse * max(cosTheta, 0.0);
		vec3 specular = positionalLights[i].specularColor * materials[materialIndex].specular * pow(max(cosPhi, 0.0), materials[materialIndex].shininess);
		vec3 ambient = positionalLights[i].ambientColor * materials[materialIndex].ambient;
		
		float dist = length(ex_VertPos - positionalLights[i].position);
		float attenuation = 1.0 / (positionalLights[i].constantAttenuation + positionalLights[i].linearAttenuation * dist + positionalLights[i].quadraticAttenuation * dist * dist);
		
		resultColor += (diffuse + specular) * attenuation + ambient;
	}
	
	vec4 noreflectColor = vec4(resultColor, materials[materialIndex].alpha) * texture(diffuseTex, ex_TexCoord);
	
	vec4 finalColor = vec4(0.0);
	
	if (envMapEnabled)
	{
		vec3 reflectedDir = reflect(eyeDir, normal);
		vec4 reflection = vec4(texture(envMap, -reflectedDir).rgb, 1.0);
		
		float cosTheta = -dot(normal, reflectedDir);
		float fresnel = pow(1 - cosTheta, 5.0);
		fresnel = max(fresnel, 0.0);
		fresnel = min(fresnel, 1.0);
		
		vec4 combinedColor = noreflectColor * (1.0 - fresnel) + reflection * fresnel;
		if (dot(eyeDir, vertexNormal) < 0.0)
		{
			finalColor = vec4(0.0);
		}
		else
		{
			finalColor = combinedColor;
		}		
	}
	else
	{
		if (dot(eyeDir, vertexNormal) < 0.0)
		{
			finalColor = vec4(0.0);
		}
		else
		{
			finalColor = noreflectColor;
		}	
	}
	
	
	float distFromCamera = length(ex_VertPos);
	float fogValue = clamp(1.0 - distFromCamera / fogDistance, 0.0, 1.0);
	fogValue = pow(fogValue, fogPower);
	
	finalColor = vec4(fogColor, 1.0) * (1.0 - fogValue) + vec4(clamp(finalColor.r, 0.0, 1.0), clamp(finalColor.g, 0.0, 1.0), clamp(finalColor.b, 0.0, 1.0), finalColor.a) * (fogValue);
	
	outColor = finalColor;
}