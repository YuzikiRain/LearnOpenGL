#pragma once
#include <GameObject.h>
#include <list>
#include <vector>

namespace BorderlessEngine
{
	class Scene
	{
	public:
		Scene();
		Scene(const char* name);
		Scene(const char* name, std::list<GameObject> gameObjects);
		const char* name;
	private:
		//std::vector<GameObject> gameObjects;
		std::list<GameObject> gameObjects;
	};
}