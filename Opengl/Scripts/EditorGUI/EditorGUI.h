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
	static void InitImgui(GLFWwindow* window)
	{
		ImGui::CreateContext();     // Setup Dear ImGui context
		ImGui::StyleColorsDark();       // Setup Dear ImGui style
		ImGui_ImplGlfw_InitForOpenGL(window, true);     // Setup Platform/Renderer backends
		ImGui_ImplOpenGL3_Init("#version 450");

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		// 启用docking
		ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;
		//ImGui::GetIO().ConfigFlags = ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_AutoHideTabBar;

		inspector = new Inspector();
		windows.push_back(inspector);
		hierarchy = new Hierarchy();
		windows.push_back(hierarchy);
	}

	static void DrawImgui()
	{
		/* Swap front and back buffers */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Window"))
			{
				for (size_t i = 0; i < windows.size(); i++)
				{
					Window& window = (*windows[i]);
					if (ImGui::MenuItem(window.name))
					{
						window.Open();
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		for (size_t i = 0; i < windows.size(); i++)
		{
			Window& window = (*windows[i]);
			if (window.isOpen)
			{
				window.BeginDraw();
				window.Draw();
				window.EndDraw();
			}
		}

		//for (vector<Window*>::iterator it = windows.begin(); it != windows.end(); it++)
		//{
		//	Window* window;

		//	window = &(it);
		//	Window w = (*it);
		//	w.BeginDraw();
		//	if (w.isOpen)
		//		w.Draw();
		//	w.EndDraw();
		//}

		ImGui::ShowDemoWindow();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	static void ShutDownEditorGUI()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

private:
	static	Inspector* inspector;
	static	Hierarchy* hierarchy;
	static vector<Window*> windows;

	static void DrawFullScreen(bool* p_open)
	{
		// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
// In this specific demo, we are not using DockSpaceOverViewport() because:
// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
// - we allow the host window to have padding (when opt_padding == true)
// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
// TL;DR; this demo is more complicated than what you would normally use.
// If we removed all the options we are showcasing, this demo would become:
//     void ShowExampleAppDockSpace()
//     {
//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
//     }

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		//else
		//{
		//    ShowDockingDisabledMessage();
		//}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
					*p_open = false;
				ImGui::EndMenu();
			}
			//HelpMarker(
			//    "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
			//    "- Drag from window title bar or their tab to dock/undock." "\n"
			//    "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
			//    "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
			//    "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
			//    "This demo app has nothing to do with enabling docking!" "\n\n"
			//    "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
			//    "Read comments in ShowExampleAppDockSpace() for more details.");

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}
};

vector<Window*> EditorGUI::windows = vector<Window*>();
Inspector* EditorGUI::inspector = 0;
Hierarchy* EditorGUI::hierarchy = 0;

