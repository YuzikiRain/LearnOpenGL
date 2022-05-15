#include <EditorGUI/EditorGUI.h>
#include <BorderlessEngine.h>
#include <Scene.h>
#include <objbase.h>
#include <windows.h>
#include <shobjidl.h> 
#include <yaml-cpp/yaml.h>
#include <Scene.h>

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
			ImGuiWindowFlags_NoSavedSettings |				// 不需要保存会加载布局信息
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

	void EditorGUI::OpenScene()
	{
		char* path = (char*)OpenFile();
		if (!path)
		{
			return;
		}

		YAML::Node scene = YAML::LoadFile(path);
		DeserializeScene(scene);
	}

	void EditorGUI::NewScene()
	{
		currentScene = BorderlessEngine::Scene();
	}

	void EditorGUI::SerializeScene()
	{
		const char* path = "D:/UnityProject/LearnOpenGL/Opengl/Assets/Scene/scene1.txt";
		//fstream  afile;
		//afile.open(path, ios::out | ios::in);
		//ofstream fout("D:/UnityProject/LearnOpenGL/Opengl/Assets/Scene/scene1.txt");
		//YAML::Node scene = YAML::LoadFile(path);
		//scene["name"] = "test22222";
		//fout << scene;
		//fout.close();
	}

	void EditorGUI::DeserializeScene(YAML::Node scene)
	{

		string scenName = scene["name"].as<string>();

		//cout << "name:" << scene["name"].as<string>() << endl;
		//cout << "sex:" << scene["sex"].as<string>() << endl;
		//cout << "age:" << scene["age"].as<int>() << endl;

		//afile.close();
	}

	void EditorGUI::CreateNewGameObject()
	{
		currentScene.AddEmptyGameObject();
	}

	vector<BorderlessEngine::GameObject*> EditorGUI::GetAllGameObjects()
	{
		return currentScene.GetAllGameObjects();
	}

	vector<Window*> EditorGUI::windows = vector<Window*>();
	Inspector* EditorGUI::inspector = 0;
	Hierarchy* EditorGUI::hierarchy = 0;
	BorderlessEngine::Scene EditorGUI::currentScene;
}