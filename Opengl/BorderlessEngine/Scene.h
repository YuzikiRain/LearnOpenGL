#pragma once
#include <GameObject.h>
#include <vector>
using namespace std;

namespace BorderlessEngine
{
	class Scene
	{
	public:
		Scene();
		Scene(const char* name);
		Scene(const char* name, vector<GameObject*> gameObjects);
		void AddEmptyGameObject();
		vector<GameObject*> GetAllGameObjects();
		const char* name;
	private:
		mutable std::vector<GameObject*> gameObjects;
	};
}