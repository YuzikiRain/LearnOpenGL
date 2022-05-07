#include <BorderlessEngine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace BorderlessEngine
{
	extern GLFWwindow* window;
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
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return 0;
	}

	void InitSystems()
	{

	}

	void UpdateSystems()
	{
	}

	void Quit()
	{
	}

	void CaculateDeltaTime()
	{
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
	}

	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);
	}
}
