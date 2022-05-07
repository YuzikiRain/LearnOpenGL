#include <ECS/System/RenderSystem.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BorderlessEngine {
	extern GLFWwindow* window;
	bool RenderSystem::Initialize()
	{
		EditorGUI::InitImgui(window);
		return true;
	}
	void RenderSystem::Update()
	{
		// ������Ȳ���
		glEnable(GL_DEPTH_TEST);
		//// �����޳�
		//glEnable(GL_CULL_FACE);
		//// ���������޳�
		//glCullFace(GL_BACK);
		// �߿�ģʽ
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		EditorGUI::DrawImgui();

		glfwSwapBuffers(window);
	}
	void RenderSystem::Destroy()
	{
		EditorGUI::ShutDownEditorGUI();
	}
}