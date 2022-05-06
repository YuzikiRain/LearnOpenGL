#pragma once
#include <iostream>
#include <EditorGUI/EditorGUI.h>

namespace BorderlessEngine {
	class RenderSystem : System
	{
	public:
		bool Initialize()
		{
			EditorGUI::InitImgui(window);
			return true;
		}
		void Update()
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
		void Destroy()
		{
			EditorGUI::ShutDownEditorGUI();
		}
	private:

	};
}