#pragma once
#include <GLFW/glfw3.h>
#include<ECS/System/InputSystem.h>
#include <ECS/System/RenderSystem.h>

namespace BorderlessEngine {
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	InputSystem inputSystem;
	RenderSystem renderSystem;

	void InitSystems()
	{
		inputSystem.Initialize();
		renderSystem.Initialize();
	}

	void UpdateSystems()
	{
		inputSystem.Update();
	}

	void CaculateDeltaTime()
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
	}
}