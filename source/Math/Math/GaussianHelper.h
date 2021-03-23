#ifndef MATH_GAUSSIAN_HELPER_H
#define MATH_GAUSSIAN_HELPER_H

#include <vector>

struct GaussianHelper
{
	static std::vector<float> computeGaussianKernel(float sigma);
};

#endif