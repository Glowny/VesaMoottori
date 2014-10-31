#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GL\glew.h"
#include "Buffers.h"
#include "ShaderProgram.h"
#include "Sprite.h"

static const GLfloat triangleData[] =
{
	-0.8f, -0.8f,		// Positio.
	1.0f, 0.0f, 0.0f,	// Väri.
	0.0f, 0.0f,			// Tekstuuri.

	-0.8f, 0.8f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f,

	0.8f, 0.8f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f,

	0.8f, -0.8f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f
};

static const GLuint indexData[] = { 0, 1, 2, 0, 2, 3 };

int main()
{
	ResourceManager resourceManager;
	Texture			texture;
	bool			isRunning = true;
	MSG				messages;
	GraphicsDevice	pekka("eitoimicustomnimi", 800, 800);
	Buffers			buffer;
	ShaderProgram	shaders;

	pekka.Register();
	pekka.Show();

	shaders.CreateShader("vertexShader.txt", GL_VERTEX_SHADER);
	shaders.CreateShader("fragmentShader.txt", GL_FRAGMENT_SHADER);
	shaders.LinkProgram();

	// Buffereiden luonti
	Sprite testSprite;


	buffer.CreateSpriteBuffer(testSprite.getVertexData(), 28 * 4, testSprite.getIndexData(), 6 * 4);
	// juu elikkäs pitäs saaha ne bufferit uloski :D:D:D:D:D:D:D:D:D:D:D:D::DD:D:D:DD:D:D::DD:D:DD
	// tuukka koodaa pls

	resourceManager.LoadPicture("goofy.png");
	texture = Texture(resourceManager.FindImage("goofy.png"));

	testSprite.setImage(resourceManager.FindImage("goofy.png"));

	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = shaders.GetAttributeLocation("attrPosition");
	const GLint colorLocation = shaders.GetAttributeLocation("attrColor");
	const GLint texLocation = shaders.GetAttributeLocation("textPosition");


	while (isRunning)
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Ikkuna ottaa vastaan viestejä.
		{
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				break;
			}

			DispatchMessage(&messages);
			pekka.Update();
			pekka.Draw();
			shaders.RunProgram();

			glBindBuffer(GL_ARRAY_BUFFER, SpriteVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, 1);

			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(colorLocation);
			glEnableVertexAttribArray(texLocation);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SpriteIndexBuffer);
			glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
			glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

			glBindTexture(GL_TEXTURE_2D, 0u);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			glBindBuffer(GL_ARRAY_BUFFER, 0u); 


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 2);
			glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
			glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
		}
	}

	return (int) messages.wParam;
}

//glBindTexture(GL_TEXTURE_2D, 0u);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
//glBindBuffer(GL_ARRAY_BUFFER, 0u);
//glDeleteTextures(1, &texture);
//glUseProgram(0);