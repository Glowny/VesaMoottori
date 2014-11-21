#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"

//static const GLfloat triangleData[] =
//{
//	-0.8f, -0.8f,		
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
	Sprite			sprite;
	Sprite			sprite2;
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
	Gooby = Resources.CreateTexture("goofy.png", "gooby", vector2f(0.0f, 0.0f), 1.0f);
	sprite.setTexture(Gooby);
	sprite2.setTexture(Gooby);
	//Gooby->CreateBuffer(triangleData, sizeof(triangleData), indexData, sizeof(indexData)); tehdään spriten kautta loopissa.


	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = Shader.GetAttributeLocation("attrPosition");
	const GLint colorLocation = Shader.GetAttributeLocation("attrColor");
	const GLint texLocation = Shader.GetAttributeLocation("textPosition");
	// physics f yes
	float wowX = 0;
	float wowY = 0;
	bool xDir = 0;
	bool yDir = 0;
	Shader.RunProgram();
	//
	while (Window.IsOpen())
	{
		// physics f yes
		if (wowX > 1.0f)
		{
			xDir = false;
		}
		if (wowX < -1.0f)
		{
			xDir = true;
		}
		if (wowY > 1.0f)
		{
			yDir = false;
		}
		if (wowY < -1.0f)
		{
			yDir = true;
		}

		if (xDir)
		{
			wowX = wowX+0.001f;
		}
		else
		{
			wowX = wowX -0.002f;
		}

		if (yDir)
		{
			wowY = wowY + 0.004f;
		}
		else
		{
			wowY = wowY - 0.003f;
		}
		sprite.setPosition(vector2f(wowX, wowY));
		sprite2.setPosition(vector2f(-wowX, -wowY));
		//
			Window.Update();
			Window.Clear();

			sprite.createVertexData();
			sprite.Draw();

			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(colorLocation);
			glEnableVertexAttribArray(texLocation);
			
			glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

			sprite2.createVertexData();
			sprite2.Draw();

			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(colorLocation);
			glEnableVertexAttribArray(texLocation);

			glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

	}

	//return (int) Messages.wParam;
	return 0;
}

//glBindTexture(GL_TEXTURE_2D, 0u);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
//glBindBuffer(GL_ARRAY_BUFFER, 0u);
//glDeleteTextures(1, &texture);
//glUseProgram(0);