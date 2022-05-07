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
#include<EditorGUI/Inspector.h>
#include<EditorGUI/Hierarchy.h>
using namespace Bordless::EditorGUI;
using namespace std;

class EditorGUI
{
public:
	static void InitImgui(GLFWwindow* window);
	static void DrawImgui();
	static void ShutDownEditorGUI();
private:
	static	Inspector* inspector;
	static	Hierarchy* hierarchy;
	static vector<Window*> windows;
};

