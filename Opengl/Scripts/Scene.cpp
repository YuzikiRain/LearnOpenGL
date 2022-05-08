#pragma once
#include <Scene.h>
#include <list>
#include <vector>

namespace BorderlessEngine
{
	Scene::Scene() : name("new scene") {}

	Scene::Scene(const char* name = "new scene")
	{

	}

	Scene::Scene(const char* name = "new scene", std::list<GameObject> gameObjects)
	{
		this->name = name;
	}
}