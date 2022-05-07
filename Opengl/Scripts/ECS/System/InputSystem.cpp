#include<ECS/System/InputSystem.h>

namespace BorderlessEngine {
	extern GLFWwindow* window;
	bool InputSystem::Initialize()
	{
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return 1;
	}
	void InputSystem::Update()
	{
		glfwPollEvents();
	}
	void InputSystem::Destroy()
	{

	}
	void InputSystem::processInput(GLFWwindow* window)
	{
	}
	//class InputSystem : System
	//{
	//public:


	//private:
	//	void processInput(GLFWwindow* window)
	//	{
	//		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//			glfwSetWindowShouldClose(window, true);

	//		//float cameraSpeed = static_cast<float>(speed * deltaTime);
	//		//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//		//	cameraPosition += cameraSpeed * cameraFront;
	//		//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//		//	cameraPosition -= cameraSpeed * cameraFront;
	//		//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//		//	cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//		//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//		//	cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//	}
	//};

	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);
	}
}