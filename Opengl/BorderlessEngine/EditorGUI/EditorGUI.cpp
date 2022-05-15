#include <EditorGUI/EditorGUI.h>
#include <BorderlessEngine.h>
#include <Scene.h>
#include <windows.h>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <Scene.h>
#include <shobjidl.h>
#include <string>

namespace BorderlessEngineEditor {
	void EditorGUI::InitImgui(GLFWwindow* window)
	{
		ImGui::CreateContext();     // Setup Dear ImGui context
		ImGui::StyleColorsDark();       // Setup Dear ImGui style
		ImGui_ImplGlfw_InitForOpenGL(window, true);     // Setup Platform/Renderer backends
		ImGui_ImplOpenGL3_Init("#version 450");

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		// 启用docking
		ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;

		inspector = new Inspector();
		windows.push_back(inspector);
		hierarchy = new Hierarchy();
		windows.push_back(hierarchy);
	}

	void EditorGUI::DrawImgui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		static bool isFrameRateOpen = false;
		ImGuiWindowFlags window_flags =
			//ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoDecoration |					// 不需要标题、不需要调整大小、不需要滚动条、不需要折叠
			ImGuiWindowFlags_AlwaysAutoResize |				// 自动调整大小
			//ImGuiWindowFlags_NoSavedSettings |				// 不需要保存会加载布局信息
			ImGuiWindowFlags_NoFocusOnAppearing |			// 显示时不需要获取交点
			ImGuiWindowFlags_NoNav;
		if (ImGui::Begin("frame rate", &isFrameRateOpen, window_flags))
		{
			ImGui::InputDouble("targetFrameRate", &BorderlessEngine::targetFrameRate, 1.0f, 5.0f, "%.2f");
			ImGui::Text("frame rate %.0lf", BorderlessEngine::GetFrameRate());
			ImGui::End();
		}

		// 主菜单
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene"))
				{
					NewScene();
				}
				if (ImGui::MenuItem("Open Scene"))
				{
					OpenScene();
				}
				if (ImGui::MenuItem("Save Scene"))
				{
					SaveScene();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window"))
			{
				for (size_t i = 0; i < windows.size(); i++)
				{
					Window& window = (*windows[i]);
					if (ImGui::MenuItem(window.name))
					{
						window.Open();
					}
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// 更新所有window
		for (size_t i = 0; i < windows.size(); i++)
		{
			Window& window = (*windows[i]);
			if (window.isOpen)
			{
				window.BeginDraw();
				window.Draw();
				window.EndDraw();
			}
		}

		//for (vector<Window*>::iterator it = windows.begin(); it != windows.end(); it++)
		//{
		//	Window* window;
		//	window = &(it);
		//	Window w = (*it);
		//	w.BeginDraw();
		//	if (w.isOpen)
		//		w.Draw();
		//	w.EndDraw();
		//}

		ImGui::ShowDemoWindow();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void EditorGUI::ShutDownEditorGUI()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	const COMDLG_FILTERSPEC fileType[] =
	{
		 { L"BorderlessEngine scene file", L"*.scene" },
	};

	PWSTR WINAPI OpenFile()
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			PWSTR pszFilePath;
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// 设置文件筛选
				pFileOpen->SetFileTypes(ARRAYSIZE(fileType), fileType);
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							return pszFilePath;
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
		return NULL;
	}

	PWSTR WINAPI SaveFile()
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			PWSTR pszFilePath;
			IFileSaveDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
				IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// 设置文件筛选
				pFileOpen->SetFileTypes(ARRAYSIZE(fileType), fileType);
				// 设置默认扩展名
				pFileOpen->SetDefaultExtension(L"scene");

				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							return pszFilePath;
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
		return NULL;
	}

	void EditorGUI::NewScene()
	{
		CloseScene();
		currentScene = new BorderlessEngine::Scene();
	}

	void EditorGUI::OpenScene()
	{
		auto path = OpenFile();
		if (!path) return;

		CloseScene();

		char pathBuffer[255];
		WideCharToMultiByte(CP_ACP, 0, path, -1, pathBuffer, sizeof(pathBuffer), NULL, NULL);
		YAML::Node sceneData = YAML::LoadFile(pathBuffer);
		auto objs = vector<BorderlessEngine::GameObject*>();

		for (size_t i = 0; i < sceneData["gameObjects"].size(); i++)
		{
			auto name = sceneData["gameObjects"][i]["name"].as<string>();
			objs.push_back(
				new BorderlessEngine::GameObject(
					name.c_str(),
					sceneData["gameObjects"][i]["isActive"].as<bool>()
				));
		}
		currentScene = new BorderlessEngine::Scene("scene", objs);
	}

	void EditorGUI::SaveScene()
	{
		auto path = SaveFile();
		if (!path) return;

		char pathBuffer[255];
		WideCharToMultiByte(CP_ACP, 0, path, -1, pathBuffer, sizeof(pathBuffer), NULL, NULL);

		fstream  sceneFileStream;
		sceneFileStream.open(path, ios::out | ios::trunc);
		YAML::Node scene;
		auto objs = currentScene->GetAllGameObjects();
		for (size_t i = 0; i < objs.size(); i++)
		{
			auto obj = objs[i];
			scene["gameObjects"][i]["name"] = obj->name;
			scene["gameObjects"][i]["isActive"] = obj->isActive;
		}

		sceneFileStream << scene;
		sceneFileStream.close();
	}

	void EditorGUI::CloseScene()
	{
		delete currentScene;
	}

	void EditorGUI::CreateNewGameObject()
	{
		currentScene->AddEmptyGameObject();
	}

	vector<BorderlessEngine::GameObject*> EditorGUI::GetAllGameObjects()
	{
		return currentScene->GetAllGameObjects();
	}

	vector<Window*> EditorGUI::windows = vector<Window*>();
	Inspector* EditorGUI::inspector = 0;
	Hierarchy* EditorGUI::hierarchy = 0;
	BorderlessEngine::Scene* EditorGUI::currentScene;
}