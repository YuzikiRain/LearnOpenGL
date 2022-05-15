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

//namespace YAML {
//	template<>
//	struct convert<BorderlessEngine::Scene> {
//		static Node encode(BorderlessEngine::Scene& rhs) {
//			Node node;
//			auto objs = (rhs).GetAllGameObjects();
//			for (size_t i = 0; i < objs.size(); i++)
//			{
//				node.push_back()
//			}
//			node.push_back(rhs.x);
//			node.push_back(rhs.y);
//			node.push_back(rhs.z);
//			return node;
//		}
//
//		static bool decode(const Node& node, BorderlessEngine::Scene& rhs) {
//			if (!node.IsSequence() || node.size() != 3) {
//				return false;
//			}
//
//			rhs.x = node[0].as<double>();
//			rhs.y = node[1].as<double>();
//			rhs.z = node[2].as<double>();
//			return true;
//		}
//	};
//}