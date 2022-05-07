#include <EditorGUI/EditorGUI.h>

void EditorGUI::InitImgui(GLFWwindow* window)
{
	ImGui::CreateContext();     // Setup Dear ImGui context
	ImGui::StyleColorsDark();       // Setup Dear ImGui style
	ImGui_ImplGlfw_InitForOpenGL(window, true);     // Setup Platform/Renderer backends
	ImGui_ImplOpenGL3_Init("#version 450");

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// ∆Ù”√docking
	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;
	//ImGui::GetIO().ConfigFlags = ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_AutoHideTabBar;

	inspector = new Inspector();
	windows.push_back(inspector);
	hierarchy = new Hierarchy();
	windows.push_back(hierarchy);
}

void EditorGUI::DrawImgui()
{
	/* Swap front and back buffers */
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

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

void EditorGUI::ShutDownEditorGUI()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

vector<Window*> EditorGUI::windows = vector<Window*>();
Inspector* EditorGUI::inspector = 0;
Hierarchy* EditorGUI::hierarchy = 0;