#pragma once
#include <Scene.h>
#include <list>
#include <vector>

namespace BorderlessEngine
{
	Scene::Scene() : name("new scene") {}

	Scene::Scene(const char* name = "new scene")
	{
		this->name = name;
	}
}