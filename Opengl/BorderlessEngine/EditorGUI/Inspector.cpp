#include <EditorGUI/Inspector.h>
#include <EditorGUI/Selection.h>
#include <GameObject.h>
#include <imgui.h>

namespace BorderlessEngineEditor
{
	const unsigned int nameLength = 30;
	Inspector::Inspector()
	{
		name = "Inspector";
	}
	void  Inspector::Draw()
	{
		if (Selection::current == NULL) return;
		BorderlessEngine::GameObject* obj = static_cast<BorderlessEngine::GameObject*>(Selection::current);
		ImGui::Checkbox("##", &obj->isActive);
		ImGui::SameLine();
		//static char name[32] = "Label1";
		//ImGui::InputText("##edit1", name, IM_ARRAYSIZE(name));

		// 这里包括最后的\0空白符，所以需要加1
		/*ImGui::InputText("##edit", obj->name, strlen(obj->name)+1);*/

		ImGui::InputText("##edit", obj->name, nameLength + 1);

	}
}
