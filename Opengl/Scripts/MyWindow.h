#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Shader.h>
#include <EditorGUI/EditorGUI.h>
#include <Model/Model.h>

const glm::vec4 clearColor = glm::vec4(.1f, .3f, .1f, 1.0f);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// lighting
glm::vec3 lightPosition(5.2f, 1.0f, -5.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

class MyWindow
{
private:
	GLFWwindow* window;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	Shader shader;
	Shader lightingShader;

public:
	int Initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return 0;
	}

	void InitShader()
	{
		shader = Shader("./Shader/vertex.shader", "./Shader/fragment.shader");
		lightingShader = Shader("./Shader/lightCubeVertex.shader", "./Shader/lightCubeFragment.shader");
	}

	void InitVertices()
	{
		// 顶点数据（位置、法线、纹理坐标）
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};
		// 顶点索引数组
		unsigned int indices[] = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		// 绑定，这样之后的DrawCall都会应用在当前绑定的VBO上
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 将用户定义的数据复制到当前绑定缓冲，即之前的VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// 处理顶点信息
		// 参数1：顶点属性的位置值，对应顶点着色器中的layout (location = 0) in vec3 aPos;顶点数据被传入该变量
		// 参数2：顶点属性大小，顶点属性是一个vec3，它由3个值组成，所以大小是3
		// 参数3：数据类型，GL_FLOAT对应float
		// 参数4：是否希望数据被标准化（Normalize），如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间
		// 参数5：步长（Stride），它告诉我们在连续的顶点属性组之间的间隔
		// 参数6：表示位置数据在缓冲中起始位置的偏移量(Offset)
		// **该函数必须要在VBO绑定后再进行调用**
		// 位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		// 以顶点属性位置值作为参数，启用顶点属性
		glEnableVertexAttribArray(0);
		// 法线属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// 纹理坐标属性
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		//// 颜色属性
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);


#pragma region MyRegion

		unsigned int lightCubeVAO;
		glGenVertexArrays(1, &lightCubeVAO);
		glBindVertexArray(lightCubeVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

#pragma endregion

		// 解绑
		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int InitTexture(const char* filename, int format, bool isFlipVertical)
	{
		// 生成纹理
		unsigned int texture;
		glGenTextures(1, &texture);
		// 绑定纹理，让之后的任何纹理指令都可以配置当前绑定的纹理
		glBindTexture(GL_TEXTURE_2D, texture);
		// 设置纹理环绕方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		// 设置纹理过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// 加载图片
		int width, height, nrChannels;
		if (isFlipVertical) stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
		if (data)
		{
			// 使用图片数据生成纹理
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			// 为当前绑定的纹理自动生成所有需要的多级渐远纹理
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else std::cout << "Failed to load texture" << filename << std::endl;

		// 生成纹理之后可以释放图片的内存数据了
		stbi_image_free(data);

		return texture;
	}

	void Render(unsigned int textures[])
	{
		glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glm::vec3 targetPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		float radius = 10.0f;

		// 开启深度测试
		glEnable(GL_DEPTH_TEST);
		//// 开启剔除
		//glEnable(GL_CULL_FACE);
		//// 开启背面剔除
		//glCullFace(GL_BACK);
		// 线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		EditorGUI::InitImgui(window);

		Model testModel = Model("./Assets/Model/nanosuit/nanosuit.obj");

		while (!glfwWindowShouldClose(window))
		{
			CaculateDeltaTime();
			processInput(window);

			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			glm::mat4 projection = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			view = glm::lookAt(
				glm::vec3(cameraPosition),
				cameraPosition + cameraFront,
				//glm::vec3(targetPosition),
				glm::vec3(cameraUp)
			);
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

#pragma region 光源

			// 光源位置、颜色
			lightingShader.use();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPosition);
			lightingShader.setMatrix4("model", model);
			lightingShader.setMatrix4("view", view);
			lightingShader.setMatrix4("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, 36);

#pragma endregion

			// 使用（激活）着色器程序对象，接下来每个着色器调用和渲染调用都会使用该着色器程序对象
			shader.use();
			// 必须激活着色器程序对象之后才能进行设置uniform变量的操作
			shader.setVector3("lightPositionWS", lightPosition);
			shader.setVector3("lightColor", lightColor);
			shader.setVector3("viewPositionWS", cameraPosition);
			shader.setMatrix4("view", view);
			shader.setMatrix4("projection", projection);

			// 先设置当前激活的纹理单元
			glActiveTexture(GL_TEXTURE0);
			// 绑定纹理到当前激活的纹理单元
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			// 同上
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			shader.setInt("texture0", 0);
			shader.setInt("texture1", 1);

			glBindVertexArray(VAO);

			for (int i = 0; i < 10; i++)
			{
				shader.setVector3("tintColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shader.setMatrix4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// render the loaded model
			//glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
			shader.setMatrix4("model", model);
			testModel.Draw(shader);

			EditorGUI::DrawImgui();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void Destroy()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shader.ID);

		EditorGUI::ShutDownEditorGUI();

		glfwDestroyWindow(window);

		glfwTerminate();
	}
};
