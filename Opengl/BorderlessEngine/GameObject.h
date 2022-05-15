#pragma once
#include <Object.h>

namespace BorderlessEngine
{
	class GameObject : public Object
	{
	public:
		GameObject(const char* newName = "New GameObject", bool isActive = true);
		
		char* name;
		bool isActive;
		~GameObject();
	private:
		void SetName(const char* name);
	};
}