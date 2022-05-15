#include "GameObject.h"
#include <cstring>

namespace BorderlessEngine
{
	const char defaultName[] = "New GameObject";
	GameObject::GameObject()
	{
		// 这里分配的内存空间为sizeof(defaultName)，而不是strlen(defaultName)
		this->name = new char[sizeof(defaultName)];
		// 否则这里copyedName的长度就会比defaultName少1，无法拷贝结束字符'\0'
		strcpy(this->name, defaultName);
		isActive = true;
	}

	GameObject::GameObject(char* name)
	{
		this->name = name;
		isActive = true;
	}

	GameObject::~GameObject()
	{
		delete[] name;
	}
}