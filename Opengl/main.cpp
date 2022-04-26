#include <MyWindow.h>

int main()
{
	MyWindow window = MyWindow();
	window.Initialize();
	window.InitShader();
	window.InitVertices();
	unsigned int texture0 = window.InitTexture("./Assets/Texture/container.jpg", GL_RGB, false);
	unsigned int texture1 = window.InitTexture("./Assets/Texture/awesomeface.png", GL_RGBA, true);
	unsigned int textures[2]{ texture0, texture1 };

	window.Render(textures);
	window.Destroy();
	return 0;
}