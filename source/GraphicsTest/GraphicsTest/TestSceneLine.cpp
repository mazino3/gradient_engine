#include <GraphicsTest/TestSceneLine.h>
#include <Graphics/Shaders/LineShader3d.h>
#include <Graphics/Camera.h>
#include <Graphics/GeometryDefinition.h>

struct TestSceneLineImpl
{
	LineShader3d lineShader;
	Camera camera;
	Mesh lineMesh;

	TestSceneLineImpl();
};

TestSceneLineImpl::TestSceneLineImpl() :
	lineMesh(GeometryDefinition::LINE)
{}

TestSceneLine::TestSceneLine(RenderTarget& renderTarget)
{
	data = std::make_unique<TestSceneLineImpl>();
	data->camera.dirFront = glm::vec3(0, 0, 1);
	data->camera.dirUp = glm::vec3(0, -1, 0);
	data->camera.setOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
}

void TestSceneLine::render(RenderTarget& renderTarget, float dt)
{
	renderTarget.bind();
	renderTarget.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	renderTarget.clear();
	
	data->lineShader.bind();
	data->lineShader.setViewMatrix(data->camera.getViewMatrix());
	data->lineShader.setProjectionMatrix(data->camera.getProjectionMatrix());
	data->lineShader.setPos1(glm::vec3(-5.0f, 3.0f, 0.0f));
	data->lineShader.setPos2(glm::vec3(4.0f, 2.0f, 0.0f));
	data->lineShader.setColor(glm::vec3(1.0f, 0.5f, 0.0f));
	
	data->lineMesh.draw();
}

void TestSceneLine::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}