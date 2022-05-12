#pragma once
#include <Object.h>

namespace BorderlessEngine
{
	class GameObject : public Object
	{
	public:
		GameObject(const char* name);
		const char* name;
	private:
	};
}