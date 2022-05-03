#pragma once

namespace Bordless
{
	namespace EditorGUI
	{
		class Window
		{
		public:
			virtual void Open()
			{
				isOpen = true;
				canClose = true;
			}
			void BeginDraw()
			{
				ImGui::Begin(name, &isOpen, ImGuiWindowFlags_None);
			}
			virtual void Draw()
			{

				//if (!isOpen)
				//{
				//	ImGui::End();
				//	return false;
				//}
				//return true;
			}
			void EndDraw()
			{
				ImGui::End();
			}
			const char* name = "Window";
			bool  isOpen;
			bool  canClose = true;
		protected:

		};
	}
}