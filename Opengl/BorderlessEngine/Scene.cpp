#pragma once
#include <Scene.h>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace BorderlessEngine
{
	Scene::Scene() : name("new scene") {}

	Scene::Scene(const char* name = "new scene")
	{
		this->name = name;
	}

	Scene::Scene(const char* name, vector<GameObject*> gameObjects)
	{
		this->name = name;
		this->gameObjects = gameObjects;
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