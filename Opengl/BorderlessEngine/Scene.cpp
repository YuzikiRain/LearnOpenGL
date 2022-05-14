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

	void Scene::AddEmptyGameObject()
	{
		this->gameObjects.push_back(new GameObject());
	}
	vector<GameObject*> Scene::GetAllGameObjects()
	{
		return this->gameObjects;
	}
}