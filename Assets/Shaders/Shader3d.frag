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

uniform int directionalLightsCount;
uniform DirectionalLight directionalLights[16];

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
	for (int i = 0; i < directionalLightsCount; i++) {
		vec3 reflection = normalize(reflect(-directionalLights[i].direction, normal));
		float cosTheta = dot(directionalLights[i].direction, normal);
		float cosPhi = dot(eyeDir, reflection);
		vec3 diffuse = directionalLights[i].diffuseColor * materials[materialIndex].diffuse * max(cosTheta, 0.0);
		vec3 specular = directionalLights[i].specularColor * materials[materialIndex].specular * pow(max(cosPhi, 0.0), materials[materialIndex].shininess);
		vec3 ambient = directionalLights[i].ambientColor * materials[materialIndex].ambient;
		resultColor += diffuse + specular + ambient;
	}	
	gl_FragColor = vec4(resultColor, 1.0) * texture(diffuseTex, ex_TexCoord);
}