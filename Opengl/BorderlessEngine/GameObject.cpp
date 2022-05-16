#include <cstring>
#include "GameObject.h"

namespace BorderlessEngine
{
	GameObject::GameObject(const char* newName, bool isActive)
	{
		SetName(newName);
		this->isActive = isActive;
	}

	GameObject::~GameObject()
	{
		delete[] name;
	}

	template<typename Component> Component* GameObject::AddComponent()
	{
		Component* component = new Component();
		components.emplace_back(component);
		return component;
	}

	template<typename Component> void GameObject::RemoveComponent(Component component)
	{
		components.remove(component);
	}

	template<typename Component> Component* GameObject::GetComponent()
	{
		for (auto i = components.begin(); i != components.end(); i++)
		{
			if (Component* component = dynamic_cast<Component*>(&(*i)))
			{
				return component;
			}
		}
		return NULL;
	}

	void GameObject::SetName(const char* name)
	{
		// 这里分配的内存空间为sizeof(defaultName)，而不是strlen(defaultName)
		this->name = new char[sizeof(name)];
		// 否则这里copyedName的长度就会比defaultName少1，无法拷贝结束字符'\0'
		strcpy(this->name, name);
	}
}