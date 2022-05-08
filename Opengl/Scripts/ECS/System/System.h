#pragma once

namespace BorderlessEngine {
	class  System
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Destroy() = 0;
	};
}