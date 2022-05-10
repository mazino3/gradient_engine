#ifndef DEPENDENCY_KEYS_H
#define DEPENDENCY_KEYS_H

#include <string>
#include "DepSupplier.h"
#include "RaycastManager.h"
#include "SelectionManager.h"
#include <Graphics/Renderer.h>

namespace DependencyKeys
{
	const DependencyKey<RaycastManager> RAYCAST_MANAGER = "raycast_manager";
	const DependencyKey<RaycastManager> HOVER_RAYCAST_MANAGER = "hover_raycast_manager";
	const DependencyKey<RaycastManager> ARROW_RAYCAST_MANAGER = "arrow_raycast_manager";
	const DependencyKey<Resources> RESOURCES = "resources";
	const DependencyKey<SelectionManager> SELECTION_MANAGER = "selection_manager";
	const DependencyKey<Renderer> RENDERER = "renderer";
}

#endif