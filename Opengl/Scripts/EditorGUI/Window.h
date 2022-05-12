#pragma once

namespace BorderlessEngineEditor
{
	class Window
	{
	public:
		virtual void Open();
		void BeginDraw();
		virtual void Draw();
		void EndDraw();
		const char* name = "Window";
		bool  isOpen;
	};
}