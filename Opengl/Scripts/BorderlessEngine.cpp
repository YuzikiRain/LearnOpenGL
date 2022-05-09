#include <BorderlessEngine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <ECS/System/InputSystem.h>
#include <ECS/System/RenderSystem.h>
#include <chrono>
#include <thread>

namespace BorderlessEngine
{
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	double targetFrameRate = 60.0;
	double realTime = 0.0;
	double frameTime = 0.0;
	double accumulator = 0.0;
	double timeScale = 1.0;
	double targetTime = 0.0;

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
		InputSystem::Initialize();
		RenderSystem::Initialize();
	}

	void GameLoop()
	{
		while (!BorderlessEngine::ShouldQuit())
		{
			InputSystem::Update();
			// 渲染可能会消耗大量时间，放在模拟时间间隔之外以避免死亡螺旋
			RenderSystem::Update();

			double currentTime = glfwGetTime();
			if (currentTime < targetTime) continue;
			frameTime = currentTime - realTime;
			realTime = currentTime;

			//accumulator += frameTime;
			//// 模拟时间间隔，剩余的未模拟时间会累计到下一帧
			//while (accumulator < currentTime)
			//{
			//	InputSystem::FixedUpdate();
			//	accumulator += interval;
			//}

			targetTime += GetFrameInterval();
			// 休眠剩余到下一次Update的时间
			if (currentTime < targetTime)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds((long)((targetTime - currentTime) * 1000)));
			}
		}
	}

	bool ShouldQuit()
	{
		return glfwWindowShouldClose(window);
	}

	double GetFrameInterval()
	{
		return 1.0 / targetFrameRate;
	}
	double GetFrameRate()
	{
		return 1.0 / frameTime;
	}

	void Quit()
	{
		InputSystem::Destroy();
		RenderSystem::Destroy();
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		//glViewport(0, 0, width, height);
	}
}
