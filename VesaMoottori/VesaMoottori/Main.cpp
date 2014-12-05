#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Keyboard.h"
#include "..\Mob.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	ResourceManager Resources;
	Texture			*Gooby;
	Texture			*Gooby2;
	Sprite			sprite, sprite2, sprite3;	
	bool			isRunning = true;
	GraphicsDevice	Window("eitoimicustomnimi", 800, 800);
	ShaderProgram	Shader;
	SpriteBatch		SpriteBatch(Window);
	Keyboard		Keys;

	Window.Register();

	Shader.AddShader(Resources.LoadShader("vertexShader.txt", "vertex"), GL_VERTEX_SHADER);
	Shader.AddShader(Resources.LoadShader("fragmentShader.txt", "fragment"), GL_FRAGMENT_SHADER);
	Shader.LinkProgram();
	SpriteBatch.SetShaderProgram(Shader);
	
	Gooby2 = Resources.CreateTexture("goofy.png", "goofy", vector2f(0.0f, 0.0f), 1.0f);
	Gooby = Resources.CreateTexture("gooby.png", "gooby", vector2f(0.0f, 0.0f), 1.0f);

	sprite.setTexture(Gooby);
	sprite2.setTexture(Gooby);
	sprite3.setTexture(Gooby);
	SpriteBatch.AddSprite(sprite3, 1);
	SpriteBatch.AddSprite(sprite2, 1);
	SpriteBatch.AddSprite(sprite, 1);

	std::vector<Mob> demoMobVector;
	demoMobVector.push_back(Mob(&sprite));
	demoMobVector.push_back(Mob(&sprite2));
	demoMobVector.push_back(Mob(&sprite3));
	for (unsigned i = 0; i < 30; i++)
	{
		Sprite* spritee = new Sprite;
		spritee->setTexture(Gooby2);
		SpriteBatch.AddSprite(*spritee, 0);
		demoMobVector.push_back(Mob(spritee));
	}

	for (unsigned i = 0; i < demoMobVector.size(); i++)
	{
		demoMobVector[i].sprite->setPosition(vector2f(0.0f, 0.0f));
	}



	sprite.setColorRGB(0.1f, 0.2f, 0.3f);
	sprite2.setColorRGB(0.4f, 0.5f, 0.6f);
	sprite3.setColorRGB(0.7f, 0.8f, 0.9f);
	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = Shader.GetAttributeLocation("attrPosition");
	const GLint colorLocation = Shader.GetAttributeLocation("attrColor");
	const GLint texLocation = Shader.GetAttributeLocation("textPosition");

	//Shader.RunProgram();
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(texLocation);

	while(Window.IsOpen())
	{
		
		for (unsigned i = 0; i < demoMobVector.size(); i++)
		{
			demoMobVector[i].speed.x = demoMobVector[i].speed.x +((rand() % 100) * 0.00001f);
			demoMobVector[i].speed.x = demoMobVector[i].speed.x - ((rand() % 100) * 0.00001f);
			demoMobVector[i].speed.y = demoMobVector[i].speed.y +((rand() % 100) * 0.00001f);
			demoMobVector[i].speed.y = demoMobVector[i].speed.y - ((rand() % 100) * 0.00001f);

			demoMobVector[i].Update();
		}
		
		//SpriteBatch.purkkaChanges();

		MSG messages;
		while(Window.Update(messages))
		{
			if(messages.message == WM_QUIT)
			{
				// Tuhotaan ikkuna, ei ole vielä koodattu.
			}
			if (Keys.isKeyPressed(Keys.Key::R))
				glClearColor(rand() % 100 * 0.01f, rand() % 100 * 0.01f, rand() % 100 * 0.01f, 1);

		}
		Window.Clear();
		SpriteBatch.Update();

		glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
		glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));

		SpriteBatch.Draw();
		
		// drawelements spritebatchsisa

		Window.Display();
	}
	glBindTexture(GL_TEXTURE_2D, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glUseProgram(0);

	return 0;
}



//return (int) Messages.wParam;
//glBindTexture(GL_TEXTURE_2D, 0u);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
//glBindBuffer(GL_ARRAY_BUFFER, 0u);
//glDeleteTextures(1, &texture);
//glUseProgram(0);