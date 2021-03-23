#include "GaussianHelper.h"
#include <math.h>

static float gaussianDensity(float x, float sigma)
{
	static float PI = 3.1415926536;
	return 1.0f / (sqrtf(2 * PI) * sigma) * expf(-x * x / (2 * sigma * sigma));
}

std::vector<float> GaussianHelper::computeGaussianKernel(float sigma)
{
	std::vector<float> result;
	int maxIndex = ceilf(sigma * 3);
	for (int i = -maxIndex; i <= maxIndex; i++)
	{
		result.push_back(gaussianDensity(i, sigma));
	}
	return result;
}