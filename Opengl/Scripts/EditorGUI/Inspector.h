#pragma once
#include <EditorGUI/Window.h>

namespace BorderlessEngine
{
	namespace EditorGUI
	{
		class Inspector : public Window
		{
		public:
			Inspector() { name = "Inspector"; }
			void  Draw()
			{
				//ImGui::Text("position: %.2f, %.2f, %.2f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
			}
		};
	}
}
