#pragma once
#include <MyWindow.h>

namespace BorderlessEngine {
	class RenderSystem : System
	{
	public:
		bool Initialize()
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
		}
		void Update()
		{
			// 开启深度测试
			glEnable(GL_DEPTH_TEST);
			//// 开启剔除
			//glEnable(GL_CULL_FACE);
			//// 开启背面剔除
			//glCullFace(GL_BACK);
			// 线框模式
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			EditorGUI::InitImgui(window);

			Model testModel = Model("./Assets/Model/nanosuit/nanosuit.obj");

			if (!glfwWindowShouldClose(window)) return;

			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			glm::mat4 projection = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			view = glm::lookAt(
				glm::vec3(cameraPosition),
				cameraPosition + cameraFront,
				//glm::vec3(targetPosition),
				glm::vec3(cameraUp)
			);
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
			shader.setMatrix4("model", model);
			testModel.Draw(shader);

			EditorGUI::DrawImgui();

			glfwSwapBuffers(window);
			glfwPollEvents();

		}

	private:
		GLFWwindow* window;
	};

}