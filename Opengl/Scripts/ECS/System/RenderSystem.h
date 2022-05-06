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
			// 开启深度测试
			glEnable(GL_DEPTH_TEST);
			//// 开启剔除
			//glEnable(GL_CULL_FACE);
			//// 开启背面剔除
			//glCullFace(GL_BACK);
			// 线框模式
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