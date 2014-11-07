#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "ShaderProgram.h"
//#define NDEBUG	// poista kommentointi tästä niin assertit poistetaan käytöstä.
#include <cassert>
//#include "Sprite.h"

//static const GLfloat triangleData[] =
//{
//	-0.8f, -0.8f,		// Positio.
//	0.0f, 0.0f, 0.0f,	// Väri.
//	0.0f, 0.0f,			// Tekstuuri.
//
//	-0.8f, 0.8f,
//	0.0f, 0.0f, 0.0f,
//	0.0f, 1.0f,
//
//	0.8f, 0.8f,
//	0.0f, 0.0f, 0.0f,
//	1.0f, 1.0f,
//
//	0.8f, -0.8f,
//	0.0f, 0.0f, 0.0f,
//	1.0f, 0.0f
//};
//
//static const GLuint indexData[] = { 0, 1, 2, 0, 2, 3 };

int main()
{
	ResourceManager Resources;
	Texture			*Gooby;
	bool			isRunning = true;
	MSG				Messages;
	GraphicsDevice	Window("eitoimicustomnimi", 800, 800);
	ShaderProgram	Shader;

	Window.Register();
	Window.Show();

	Shader.AddShader(Resources.LoadShader("vertexShader.txt", "vertex"), GL_VERTEX_SHADER);
	Shader.AddShader(Resources.LoadShader("fragmentShader.txt", "fragment"), GL_FRAGMENT_SHADER);
	Shader.LinkProgram();

	Resources.LoadPicture("goofy.png");
	Gooby = Resources.CreateTexture("goofy.png", "gooby", vector2f(100.0f, 100.0f), 200.0f);
	//Gooby = Resources.CreateTexture("goofy.png", "gooby");
	//Gooby->CreateBuffer(triangleData, sizeof(triangleData), indexData, sizeof(indexData));


	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = Shader.GetAttributeLocation("attrPosition");
	const GLint colorLocation = Shader.GetAttributeLocation("attrColor");
	const GLint texLocation = Shader.GetAttributeLocation("textPosition");

	assert(posLocation != -1);
	assert(colorLocation != -1);
	assert(texLocation != -1);

	while (isRunning)
	{
		while (PeekMessage(&Messages, NULL, 0, 0, PM_REMOVE)) // Ikkuna ottaa vastaan viestejä.
		{
			if (Messages.message == WM_QUIT)
			{
				isRunning = false;
				break;
			}

			DispatchMessage(&Messages);
			Window.Update();
			Window.Clear();

			Shader.RunProgram();
			Gooby->Draw();

			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(colorLocation);
			glEnableVertexAttribArray(texLocation);

			glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
		}
	}

	return (int) Messages.wParam;
}

//glBindTexture(GL_TEXTURE_2D, 0u);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
//glBindBuffer(GL_ARRAY_BUFFER, 0u);
//glDeleteTextures(1, &texture);
//glUseProgram(0);