#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Keyboard.h"


int main()
{
	ResourceManager Resources;
	Texture			*Gooby;
	//Texture		*Gooby2;
	Sprite			sprite, sprite2, sprite3;	
	bool			isRunning = true;
	GraphicsDevice	Window("eitoimicustomnimi", 800, 800);
	ShaderProgram	Shader;
	SpriteBatch		SpriteBatch(Window);
	Keyboard		Keys;

	Shader.AddShader(Resources.LoadShader("vertexShader.txt", "vertex"), GL_VERTEX_SHADER);
	Shader.AddShader(Resources.LoadShader("fragmentShader.txt", "fragment"), GL_FRAGMENT_SHADER);
	Shader.LinkProgram();

	SpriteBatch.SetShaderProgram(Shader);

<<<<<<< HEAD
<<<<<<< HEAD
	//Gooby2 = Resources.CreateTexture("goofy.png", "goofy", vector2f(0.0f, 0.0f), 1.0f);
	Gooby = Resources.CreateTexture("gooby.png", "gooby");
=======
=======
>>>>>>> parent of f6e486e... Ei toimi vielä
	Gooby2 = Resources.CreateTexture("goofy.png", "goofy", vector2f(0.0f, 0.0f), 1.0f);
	Gooby = Resources.CreateTexture("gooby.png", "gooby", vector2f(0.0f, 0.0f), 1.0f);
>>>>>>> parent of f6e486e... Ei toimi vielä

	sprite.setTexture(Gooby);
	sprite2.setTexture(Gooby2);
	sprite3.setTexture(Gooby);

	SpriteBatch.AddSprite(sprite3, 1);
	SpriteBatch.AddSprite(sprite2, 1);
	SpriteBatch.AddSprite(sprite, 2);

	sprite.setColorRGB(0.1f, 0.2f, 0.3f);
	sprite2.setColorRGB(0.4f, 0.5f, 0.6f);
	sprite3.setColorRGB(0.7f, 0.8f, 0.9f);
	// Tarkistetaan attribuuttien lokaatio.

	//const GLint posLocation = Shader.GetAttributeLocation("attrPosition");
	//const GLint colorLocation = Shader.GetAttributeLocation("attrColor");
	//const GLint texLocation = Shader.GetAttributeLocation("textPosition");
	//glEnableVertexAttribArray(posLocation);
	//glEnableVertexAttribArray(colorLocation);
	//glEnableVertexAttribArray(texLocation);

	float wowX = 0;
	float wowY = 0;
	bool xDir = 0;
	bool yDir = 0;

	while(Window.IsOpen())
	{
		if(wowX > 1.0f)
		{
			xDir = false;
		}
		if(wowX < -1.0f)
		{
			xDir = true;
		}
		if(wowY > 1.0f)
		{
			yDir = false;
		}
		if(wowY < -1.0f)
		{
			yDir = true;
		}

		if(xDir)
		{
			wowX = wowX+0.001f;
		}
		else
		{
			wowX = wowX -0.002f;
		}

		if(yDir)
		{
			wowY = wowY + 0.004f;
		}
		else
		{
			wowY = wowY - 0.003f;
		}
		sprite2.setPosition(vector2f(-wowX, -wowY));
		sprite.setPosition(vector2f(wowX, wowY));
		sprite3.setPosition(vector2f(0.5, 0.5));
		
		//SpriteBatch.purkkaChanges();

		MSG messages;
		while(Window.Update(messages))
		{
			if(messages.message == WM_QUIT)
			{
				// Tuhotaan ikkuna, ei ole viel� koodattu.
			}
			if (Keys.isKeyPressed(Keys.Key::R))
				glClearColor(rand() % 100 * 0.01f, rand() % 100 * 0.01f, rand() % 100 * 0.01f, 1);
		}
<<<<<<< HEAD
=======
		Window.Clear();
		SpriteBatch.Update();

		glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
		glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
>>>>>>> parent of f6e486e... Ei toimi vielä

		Window.Clear();
		SpriteBatch.Draw();
		Window.Display();

		//SpriteBatch.Update();
		//glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		//glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
		//glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
		// drawelements spritebatchsisa
	}

	return 0;
}

//return (int) Messages.wParam;
//glBindTexture(GL_TEXTURE_2D, 0u);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
//glBindBuffer(GL_ARRAY_BUFFER, 0u);
//glDeleteTextures(1, &texture);
//glUseProgram(0);