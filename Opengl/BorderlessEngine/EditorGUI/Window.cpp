#include<EditorGUI/Window.h>
#include <imgui.h>

namespace BorderlessEngineEditor
{
	void Window::Open()
	{
		isOpen = true;
	}
	void Window::BeginDraw()
	{
		ImGui::Begin(name, &isOpen, ImGuiWindowFlags_None);
	}
	void Window::Draw()
	{
	}
	void Window::EndDraw()
	{
		ImGui::End();
	}
	const char* name = "Window";
	bool  isOpen;
}