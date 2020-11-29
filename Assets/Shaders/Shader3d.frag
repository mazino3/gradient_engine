#version 130
precision highp float;

struct MaterialProperties {
	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
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

uniform int positionalLightsCount;
uniform PositionalLight positionalLights[16];

uniform int materialIndex;
uniform MaterialProperties materials[16];

uniform vec3 eyeDirection;
uniform sampler2D diffuseTex;

in vec4 ex_Color;
in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_VertPos;
out vec4 gl_FragColor;

void main(void) {
	vec3 resultColor = vec3(0.0, 0.0, 0.0);
	vec3 normal = normalize(ex_Normal);
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
	
	//positional lights
	for (int i = 0; i < positionalLightsCount; i++) {
		vec3 direction = ex_VertPos - positionalLights[i].position;
		vec3 reflection = normalize(reflect(-direction, normal));
		float cosTheta = dot(direction, normal);
		float cosPhi = dot(eyeDir, reflection);
		vec3 diffuse = positionalLights[i].diffuseColor * materials[materialIndex].diffuse * max(cosTheta, 0.0);
		vec3 specular = positionalLights[i].specularColor * materials[materialIndex].specular * pow(max(cosPhi, 0.0), materials[materialIndex].shininess);
		vec3 ambient = positionalLights[i].ambientColor * materials[materialIndex].ambient;
		
		float dist = distance(ex_VertPos, positionalLights[i].position);
		float attenuation = 1.0 / (positionalLights[i].constantAttenuation + positionalLights[i].linearAttenuation * dist + positionalLights[i].quadraticAttenuation * dist * dist);
		
		resultColor += (diffuse + specular) * attenuation + ambient;
	}
	
	
	gl_FragColor = vec4(resultColor, 1.0) * texture(diffuseTex, ex_TexCoord);
}