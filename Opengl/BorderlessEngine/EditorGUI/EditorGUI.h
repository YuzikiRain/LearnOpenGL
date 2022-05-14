#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <stdio.h>
//#include <Windows.h>
#include <tchar.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <vector>

// 所有需要的editorwindow子类
#include<EditorGUI/Window.h>
#include<EditorGUI/Inspector.h>
#include<EditorGUI/Hierarchy.h>
#include <Scene.h>
#include <yaml-cpp/yaml.h>
#include <GameObject.h>

using namespace std;

namespace BorderlessEngineEditor {
	class EditorGUI
	{
	public:
		static void InitImgui(GLFWwindow* window);
		static void DrawImgui();
		static void ShutDownEditorGUI();

		/// <summary>
		/// 打开场景
		/// </summary>
		static void OpenScene();
		/// <summary>
		/// 创建新GameObject
		/// </summary>
		static void CreateNewGameObject();
		static void NewScene();
		static void SerializeScene();
		static void DeserializeScene(YAML::Node scene);
		static vector<BorderlessEngine::GameObject*> GetAllGameObjects();
	private:
		static BorderlessEngineEditor::Inspector* inspector;
		static BorderlessEngineEditor::Hierarchy* hierarchy;
		static BorderlessEngine::Scene currentScene;
		static vector<BorderlessEngineEditor::Window*> windows;
	};
}
