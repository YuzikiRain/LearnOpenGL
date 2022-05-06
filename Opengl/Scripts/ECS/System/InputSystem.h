#pragma once
#include<ECS/System/System.h>

namespace BorderlessEngine {
	class InputSystem : System
	{
	public:
		bool Initialize();
		void Update();
		void Destroy();

	private:
		void processInput(GLFWwindow* window);
	};

	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
}