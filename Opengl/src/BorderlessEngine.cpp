#pragma once
#include <BorderlessEngine.h>
#include <ECS/System/InputSystem.h>
#include <ECS/System/RenderSystem.h>

namespace BorderlessEngine {
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	static InputSystem inputSystem;
	static RenderSystem renderSystem;

	bool InitializeWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		return 0;
	}

	void InitSystems()
	{
		inputSystem.Initialize();
		renderSystem.Initialize();
	}

	void UpdateSystems()
	{
		while (!glfwWindowShouldClose(window))
		{
			inputSystem.Update();
			renderSystem.Update();
		}
	}

	void Quit()
	{
		inputSystem.Destroy();
		renderSystem.Destroy();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void CaculateDeltaTime()
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}