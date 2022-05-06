#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BorderlessEngine {
	bool InitializeWindow();
	void InitSystems();
	void UpdateSystems();
	void Quit();
	void CaculateDeltaTime();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	GLFWwindow* window;
}