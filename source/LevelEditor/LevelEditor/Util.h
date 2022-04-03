#ifndef LEVEL_EDITOR_UTIL_H
#define LEVEL_EDITOR_UTIL_H

#include <Graphics/GeometryDefinition.h>

namespace Util
{
	GeometryDefinition createGridGeometry(float size, float cellSize, float subSize);
};

#endif