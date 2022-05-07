#include <BorderlessEngine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ECS/System/InputSystem.h>
#include <ECS/System/RenderSystem.h>
namespace BorderlessEngine
{
	GLFWwindow* window;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

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

	void BorderlessEngine::InitSystems()
	{
		InputSystem::Initialize();
		RenderSystem::Initialize();
	}

	void BorderlessEngine::UpdateSystems()
	{
		while (!BorderlessEngine::ShouldQuit())
		{
			InputSystem::Update();
			RenderSystem::Update();
		}
	}

	bool BorderlessEngine::ShouldQuit()
	{
		return glfwWindowShouldClose(window);
	}

	void Quit()
	{
		InputSystem::Destroy();
		RenderSystem::Destroy();
	}

	void CaculateDeltaTime()
	{
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
	}
}
