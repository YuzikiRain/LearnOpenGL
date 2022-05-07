#pragma once
#include<ECS/System/System.h>
#include <EditorGUI/EditorGUI.h>

namespace BorderlessEngine {
	class RenderSystem : System
	{
	public:
		static bool Initialize();
		static void Update();
		static void Destroy();
	private:

	};
}