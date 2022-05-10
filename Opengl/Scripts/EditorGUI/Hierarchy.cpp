#include <EditorGUI/Hierarchy.h>
#include <imgui.h>
#include <EditorGUI/EditorGUI.h>

namespace BorderlessEngineEditor
{
	Hierarchy::Hierarchy()
	{
		name = "Hierarchy";
	}
	void  Hierarchy::Draw()
	{
		if (ImGui::BeginPopupContextWindow()) {
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("GameObject"))
				{
					BorderlessEngineEditor::EditorGUI::CreateNewGameObject();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		auto objs = EditorGUI::GetAllGameObjects();
		for (size_t i = 0; i < objs.size(); i++)
		{
			BorderlessEngine::GameObject obj = objs[i];
			if (ImGui::TreeNode((void*)(intptr_t)i, obj.name, i))
			{

			}
		}


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
					if (ImGui::BeginPopupContextItem())
					{
						ImGui::Text("Edit name:");
						//ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));
						if (ImGui::Button("Close"))
							ImGui::CloseCurrentPopup();
						ImGui::EndPopup();
					}
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}
}