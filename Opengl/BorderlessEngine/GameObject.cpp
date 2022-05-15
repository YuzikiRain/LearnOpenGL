#include "GameObject.h"
#include <cstring>

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
	void GameObject::SetName(const char* name)
	{
		// 这里分配的内存空间为sizeof(defaultName)，而不是strlen(defaultName)
		this->name = new char[sizeof(name)];
		// 否则这里copyedName的长度就会比defaultName少1，无法拷贝结束字符'\0'
		strcpy(this->name, name);
	}
}