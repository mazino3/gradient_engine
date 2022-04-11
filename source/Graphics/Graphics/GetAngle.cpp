#include <Graphics/GetAngle.h>
#include <cmath>

float getAngle(const glm::vec2& direction)
{
	static const float PI = 3.14159265f;
	static const float EPS = 0.00001f;

	if (std::fabsf(direction.x) < EPS)
	{
		return direction.y > 0 ? 0 : PI;
	}

	if (direction.x < 0)
	{
		return std::atanf(direction.y / direction.x) + PI;
	}
	else
	{
		if (direction.y > 0)
		{
			return std::atanf(direction.y / direction.x);
		}
		else
		{
			return std::atanf(direction.y / direction.x) + PI * 2;
		}
	}
}

float getAngle(float x, float y)
{
	return getAngle(glm::vec2(x, y));
}