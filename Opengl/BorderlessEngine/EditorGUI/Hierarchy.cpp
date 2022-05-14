#include <EditorGUI/Hierarchy.h>
#include <imgui.h>
#include <EditorGUI/EditorGUI.h>
#include <EditorGUI/Selection.h>

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

		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		auto objs = EditorGUI::GetAllGameObjects();
		for (size_t i = 0; i < objs.size(); i++)
		{
			auto obj = objs[i];
			ImGuiTreeNodeFlags node_flags = base_flags;
			if (BorderlessEngineEditor::Selection::current == obj) node_flags |= ImGuiTreeNodeFlags_Selected;
			bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, obj->name);
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				BorderlessEngineEditor::Selection::current = obj;
			}
			if (node_open)
			{
				ImGui::TreePop();
			}

			//ImGui::Text("obj:%d %p\n", i, obj);
			//printf("%p\n", &obj);
			//if (ImGui::Selectable(obj->name, BorderlessEngineEditor::Selection::current == obj))
			//{
			//	BorderlessEngineEditor::Selection::current = obj;
			//}
		}
		ImGui::Text("current %p\n", BorderlessEngineEditor::Selection::current);

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
