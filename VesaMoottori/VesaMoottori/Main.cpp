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
	Texture			*Gooby, *Gooby2, *Animation, *Explosion;
	Sprite			sprite, sprite2, sprite3, animationSprite, explosion;
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
	
	// DEMOA //


	Animation = Resources.CreateTexture("Animation.png", "Animation", vector2f(0.0f, 0.0f), 1.0f);
	Explosion = Resources.CreateTexture("exp2.png", "Explosion", vector2f(0.0f, 0.0f),1.0f);
	Gooby2 = Resources.CreateTexture("goofy.png", "goofy", vector2f(0.0f, 0.0f), 1.0f);
	Gooby = Resources.CreateTexture("gooby.png", "gooby", vector2f(0.0f, 0.0f), 1.0f);

	animationSprite.setTexture(Animation);
	explosion.setTexture(Explosion);

	sprite.setTexture(Gooby2);
	sprite.setSize(vector2f(150, 150));
	sprite.setOrigin(vector2f(75,75));
	sprite.setPosition(vector2f(750, 750));
	sprite2.setTexture(Gooby);
	sprite2.setSize(vector2f(10, 10));

	sprite3.setTexture(Gooby2);
	sprite3.setSize(vector2f(20, 20));

	std::vector<Mob> demoMobVector; // Tällä vektorilla liikutetaan.
	demoMobVector.push_back(Mob(&sprite));
	demoMobVector.push_back(Mob(&sprite3));
	demoMobVector.push_back(Mob(&animationSprite, true));
	demoMobVector.push_back(Mob(&explosion, true));
	animationSprite.setSourceRSize(vector2f(64.0f, 64.0f));
	explosion.setSourceRSize(vector2f(64.0f, 64.0f));
	for (unsigned i = 0; i < 10; i++)
	{
		Sprite* spritee = new Sprite;
		spritee->setTexture(Gooby);
		spritee->setSize(vector2f(50 * (i%5), 50 * (i%5)));
		SpriteBatch.AddSprite(*spritee, 3);
		demoMobVector.push_back(Mob(spritee));
	}

	SpriteBatch.AddSprite(sprite2, 1);
	SpriteBatch.AddSprite(sprite, 1);
	SpriteBatch.AddSprite(animationSprite, 0);
	SpriteBatch.AddSprite(sprite3, 0);
	SpriteBatch.AddSprite(explosion, 0);

	for (unsigned i = 0; i < demoMobVector.size(); i++)
	{
		demoMobVector[i].sprite->setPosition(vector2f(0.0f, 0.0f));
	}


	
	

	sprite.setColorRGB(255.0f, 255.0f, 255.0f);
	sprite2.setColorRGB(255.0f, 255.0f, 255.0f);
	sprite3.setColorRGB(255.0f, 255.0f, 255.0f);

	// DEMO LOPPU //


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
		
		// DEMOA //
		for (unsigned i = 0; i < demoMobVector.size(); i++)
		{
			demoMobVector[i].speed.x = demoMobVector[i].speed.x +((rand() % 100) * 0.001f);
			demoMobVector[i].speed.x = demoMobVector[i].speed.x - ((rand() % 100) * 0.001f);
			demoMobVector[i].speed.y = demoMobVector[i].speed.y +((rand() % 100) * 0.001f);
			demoMobVector[i].speed.y = demoMobVector[i].speed.y - ((rand() % 100) * 0.001f);
			demoMobVector[i].Update();
			if (demoMobVector[i].animationEnabled == true)
			{
				demoMobVector[i].ChangeFrame();
			}
		}

		// DEMO LOPPU //

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
		
		SpriteBatch.Update();	// vertexAttribPointerien täytyy olla updaten ja drawin välissä, pitäskö hakea
		// spritebatchissa olevalla shaderprogramilla?
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