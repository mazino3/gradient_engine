#include "BlurShader.h"
#include "../Math/GaussianHelper.h"
#include <string>
#include <iostream>

BlurShader::BlurShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/BlurShader.vert", "Assets/Shaders/BlurShader.frag") 
{}

static std::string vertexShaderHeader =
"#version 130\n"
"in vec3 in_Position;\n"
"in vec4 in_Color;\n"
"in vec2 in_TexCoords;\n"
"uniform float pixelSize;\n"
"uniform bool isHorizontal;\n";

static std::string generateVertexShader(const std::vector<float>& kernel)
{
	std::string halfSize = std::to_string(kernel.size() / 2);
	std::string size = std::to_string(kernel.size());

	std::string shaderCode = vertexShaderHeader;
	shaderCode +=
		"out vec2 texCoords[" + size + "];\n"
		"void main(void)\n"
		"{\n"
		"	gl_Position = vec4(in_Position, 1.0);\n"
		"	vec2 centerTexCoords = in_Position.xy / 2 + 0.5;\n"
		"	for(int i = -" + halfSize + "; i <= " + halfSize + "; i++)\n"
		"	{\n"
		"		if (isHorizontal)\n"
		"		{\n"
		"			texCoords[i + " + halfSize + "] = centerTexCoords + vec2(pixelSize, 0.0) * i;\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			texCoords[i + " + halfSize + "] = centerTexCoords + vec2(0.0, pixelSize) * i;\n"
		"		}\n"
		"	}\n"
		"}\n";

	return shaderCode;
}

static std::string generateVertexShaderBigRadius()
{
	std::string result;
	result += vertexShaderHeader;
	result +=
		"out vec2 texCoords;\n"
		"void main(void)\n"
		"{\n"
		"	gl_Position = vec4(in_Position, 1.0);\n"
		"	texCoords = in_Position.xy / 2 + 0.5;\n"
		"}\n";
	return result;
}

static std::string getKernelDeclarationStr(const std::vector<float>& kernel)
{
	std::string size = std::to_string(kernel.size());

	std::string kernelStr = "float kernel[" + size + "] = float[" + size + "](";
	for (int i = 0; i < kernel.size(); i++)
	{
		kernelStr += std::to_string(kernel[i]);
		if (i != kernel.size() - 1)
		{
			kernelStr += ", ";
		}
	}
	kernelStr += ");";

	return kernelStr;
}

static std::string generateFragmentShaderBigRadius(const std::vector<float>& kernel)
{
	std::string halfSize = std::to_string(kernel.size() / 2);
	std::string size = std::to_string(kernel.size());

	std::string shaderCode =
		"#version 130\n"
		"in vec2 texCoords;\n"
		"uniform sampler2D screenTexture;\n"
		"uniform float pixelSize;\n"
		"uniform bool isHorizontal;\n"
		"void main(void)\n"
		"{\n" +
		getKernelDeclarationStr(kernel) + "\n"
		"	gl_FragColor = vec4(0.0);\n"
		"	for(int i = -" + halfSize + "; i <= " + halfSize + "; i++)\n"
		"	{\n"
		"		if (isHorizontal)\n"
		"		{\n"
		"			gl_FragColor += texture(screenTexture, texCoords + vec2(pixelSize, 0.0) * i) * kernel[i + " + halfSize + "];\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			gl_FragColor += texture(screenTexture, texCoords + vec2(0.0, pixelSize) * i) * kernel[i + " + halfSize + "];\n"
		"		}\n"
		"	}\n"
		"}\n";

	return shaderCode;
}

static std::string generateFragmentShader(const std::vector<float>& kernel)
{
	std::string halfSize = std::to_string(kernel.size() / 2);
	std::string size = std::to_string(kernel.size());

	std::string shaderCode =
		"#version 130\n"
		"in vec2 texCoords[" + size + "];\n"
		"uniform sampler2D screenTexture;\n"
		"void main(void)\n"
		"{\n" + 
			getKernelDeclarationStr(kernel) + "\n"
		"	gl_FragColor = vec4(0.0);\n"
		"	for (int i = 0; i < " + size + "; i++)\n"
		"	{\n"
		"		gl_FragColor += texture(screenTexture, texCoords[i]) * kernel[i];\n"
		"	}\n"
		"}\n";

	return shaderCode;
}

BlurShader::BlurShader(float radius)
{
	float sigma = radius / 3.0f;
	auto kernel = GaussianHelper::computeGaussianKernel(sigma);
	bool bigRadius = kernel.size() > 11;
	auto vertexCode = bigRadius ? generateVertexShaderBigRadius() : generateVertexShader(kernel);
	auto fragmentCode = bigRadius ? generateFragmentShaderBigRadius(kernel) : generateFragmentShader(kernel);

	std::cout << "big radius: " << (bigRadius ? "yes" : "no") << std::endl;

	std::cout << "vertex code: " << vertexCode << std::endl;
	std::cout << "fragment code: " << fragmentCode << std::endl;

	init(ShaderInitType::Code, vertexCode, fragmentCode);
}

void BlurShader::setScreenTexture(Texture& texture)
{
	texture.bind(0);
	setUniform("screenTexture", 0);
}

void BlurShader::setPixelSize(float pixelSize)
{
	setUniform("pixelSize", pixelSize);
}

void BlurShader::setHorizontal(bool isHorizontal)
{
	setUniform("isHorizontal", isHorizontal ? 1 : 0);
}