#include "Util.h"

GeometryDefinition Util::createGridGeometry(float size, float cellSize, float subSize)
{
	static float eps = 0.01f;

	GeometryDefinition result(MeshType::Lines);

	for (float offset = -size / 2; offset <= size / 2; offset += cellSize)
	{
		for (int i = -1; i <= 1; i++)
		{
			GeometryDefinition lineX = GeometryDefinition::LINE_X
				.scale(glm::vec3(size, 1, 1))
				.translate(glm::vec3(-size / 2, offset + eps * i, 0));
			GeometryDefinition lineY = GeometryDefinition::LINE_Y
				.scale(glm::vec3(1, size, 1))
				.translate(glm::vec3(offset + eps * i, -size / 2, 0));

			result = result + lineX + lineY;
		}


		for (float subOffset = offset + subSize; subOffset <= offset + cellSize - subSize + eps; subOffset += subSize)
		{
			GeometryDefinition lineX = GeometryDefinition::LINE_X
				.scale(glm::vec3(size, 1, 1))
				.translate(glm::vec3(-size / 2, subOffset, 0));
			GeometryDefinition lineY = GeometryDefinition::LINE_Y
				.scale(glm::vec3(1, size, 1))
				.translate(glm::vec3(subOffset, -size / 2, 0));

			result = result + lineX + lineY;
		}
	}

	return result;
}