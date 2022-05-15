#pragma once
#include <Object.h>

namespace BorderlessEngine
{
	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(char* name);
		char* name;
		bool isActive;
		~GameObject();
	private:
	};
}