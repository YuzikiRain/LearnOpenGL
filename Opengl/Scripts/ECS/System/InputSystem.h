#pragma once
#include<ECS/System/System.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BorderlessEngine {
	class InputSystem : System
	{
	public:
		static bool Initialize();
		static void Update();
		static void Destroy();

	private:
		void processInput(GLFWwindow* window);
	};

	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
}