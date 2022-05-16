#pragma once
#include <Object.h>
#include <ECS/Component/Component.h>
#include <list>

namespace BorderlessEngine
{
	class GameObject : public Object
	{
	public:
		GameObject(const char* newName = "New GameObject", bool isActive = true);
		~GameObject();
		template<typename Component> Component* AddComponent();
		template<typename Component> void RemoveComponent(Component component);
		template<typename Component> Component* GetComponent();
		std::list<Component> components;
		char* name;
		bool isActive;
	private:
		void SetName(const char* name);
	};
}