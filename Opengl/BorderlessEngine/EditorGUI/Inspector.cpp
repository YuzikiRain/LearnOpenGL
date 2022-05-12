#include <EditorGUI/Inspector.h>
#include <EditorGUI/Selection.h>
#include <GameObject.h>

namespace BorderlessEngineEditor
{
	Inspector::Inspector()
	{
		name = "Inspector";
	}
	void  Inspector::Draw()
	{
		BorderlessEngine::GameObject* obj = Selection::current;
	}
}
