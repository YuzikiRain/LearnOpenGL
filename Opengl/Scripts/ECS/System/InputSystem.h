#pragma once
#include<ECS/System/System.h>

namespace BorderlessEngine {
	class InputSystem : System
	{
	public:
		bool Initialize()
		{
			return 1;
		}

		void Update()
		{

		}

	private:
		void processInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);

			//float cameraSpeed = static_cast<float>(speed * deltaTime);
			//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			//	cameraPosition += cameraSpeed * cameraFront;
			//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			//	cameraPosition -= cameraSpeed * cameraFront;
			//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			//	cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			//	cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
		{
			float xpos = static_cast<float>(xposIn);
			float ypos = static_cast<float>(yposIn);
		}
	};
}