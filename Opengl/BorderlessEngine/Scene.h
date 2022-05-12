#pragma once
#include <GameObject.h>
#include <list>
#include <vector>
using namespace std;

namespace BorderlessEngine
{
	class Scene
	{
	public:
		Scene();
		Scene(const char* name);
		Scene(const char* name, list<GameObject> gameObjects);
		void AddEmptyGameObject();
		vector<GameObject> GetAllGameObjects();
		const char* name;
	private:
		//std::vector<GameObject> gameObjects;
		std::vector<GameObject> gameObjects;
	};
}