#pragma once
#include <EditorGUI/Window.h>
#include <EditorGUI/Selection.h>

namespace Bordless
{
	namespace EditorGUI
	{
		class Hierarchy : public Window
		{
		public:
			Hierarchy()
			{
				name = "Hierarchy";
			}
			void  Draw()
			{
				if (ImGui::TreeNode("Basic trees"))
				{
					for (int i = 0; i < 5; i++)
					{
						// Use SetNextItemOpen() so set the default state of a node to be open. We could
						// also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
						if (i == 0)
							ImGui::SetNextItemOpen(true, ImGuiCond_Once);

						if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
						{
							//Selection::current = ;

							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
			}
		};
	}
}
