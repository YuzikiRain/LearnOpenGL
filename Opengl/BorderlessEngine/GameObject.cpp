#include "GameObject.h"
#include <cstring>
#include <string.h>
#include <stdio.h>

namespace BorderlessEngine
{
	const char* defaultName = "New GameObject";
	GameObject::GameObject()
	{
		this->name = new char[strlen(defaultName)];
		strcpy(this->name, defaultName);
		isActive = true;
	}

	GameObject::GameObject(char* name)
	{
		this->name = name;
		isActive = true;
	}
}