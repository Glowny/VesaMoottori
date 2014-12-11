#include "Demo.h"


Demo::Demo()
{
	window = new GraphicsDevice("Demo", 1800, 1200);
	LoadResources();
	InitShaders();
	InitSpriteBatches();
}

void Demo::LoadResources()
{
	resourceManager.LoadShader("vertexShader.txt", "vertex");
	resourceManager.LoadShader("fragmentShader.txt", "fragment");

	resourceManager.CreateTexture("Animation.png", "Animation"); 
	resourceManager.CreateTexture("exp2.png", "Explosion");
	resourceManager.CreateTexture("goofy.png", "goofy");
	resourceManager.CreateTexture("gooby.png", "gooby");
}

void Demo::InitShaders()
{
	shader.AddShader(resourceManager.FindShader("vertex"), GL_VERTEX_SHADER);
	shader.AddShader(resourceManager.FindShader("fragment"), GL_VERTEX_SHADER);
	shader.LinkProgram();

	shader.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	shader.AddVertexAttribPointer("attrColor", 3, 7, 2);
	shader.AddVertexAttribPointer("textPosition", 2, 7, 5);
}

void Demo::InitSpriteBatches()
{
	spriteBatch = SpriteBatch(*window);
	spriteBatch.SetShaderProgram(shader);
}
	float sizeMultipler = 1;
	bool dir = true;
	float currentColor[3];
void Demo::SceneOne()
{

	Sprite animation, resize, colorChange;

	animation.setTexture(resourceManager.FindTexture("Animation"));
	animation.setSize(vector2f(92.0f, 92.0f));
	animation.setSourceRSize(vector2f(64.0f, 64.0f));

	resize.setTexture(resourceManager.FindTexture("gooby"));

	colorChange.setTexture(resourceManager.FindTexture("gooby"));
	colorChange.setSize(vector2f(100, 100));
	colorChange.setPosition(vector2f(600, 600));

	spriteBatch.AddSprite(animation, 0);
	spriteBatch.AddSprite(resize, 0);
	spriteBatch.AddSprite(colorChange, 0);
	mobV.push_back(&animation);
	mobV.push_back(&resize);
	/*mobV.push_back(&colorChange);*/

	for (int i = 0; i < 10; i++)
	{
		Sprite* sprite = new Sprite;
		sprite->setTexture(resourceManager.FindTexture("gooby"));
		sprite->setSize(vector2f(50.0f * (i % 5), 50.0f * (i % 5)));
		sprite->setPosition(vector2f(500, 500));
		spriteBatch.AddSprite(*sprite, 3);
		mobV.push_back(sprite);
	}

	while (window->IsOpen())	// Tähän joku toinen quittiehto.
	{
		for (unsigned i = 0; i < mobV.size(); i++)
		{
			mobV[i].speed.x = mobV[i].speed.x + ((rand() % 100) * 0.001f);
			mobV[i].speed.x = mobV[i].speed.x - ((rand() % 100) * 0.001f);
			mobV[i].speed.y = mobV[i].speed.y + ((rand() % 100) * 0.001f);
			mobV[i].speed.y = mobV[i].speed.y - ((rand() % 100) * 0.001f);
			mobV[i].Update();

			if (mobV[i].animationEnabled == true)
			{
				mobV[i].ChangeFrame();
			}
		}
		//
		resize.setSize(vector2f(sizeMultipler * 300, sizeMultipler * 300));
		if (sizeMultipler > 1)
		{
			dir = false;
		}
		else if (sizeMultipler < 0)
		{
			dir = true;
		}
		if (dir)
		{
			sizeMultipler = sizeMultipler + 0.01f;
		}
		else
		{
			sizeMultipler = sizeMultipler - 0.01f;
		}
		//

		colorChange.setColorRGB(currentColor[0], currentColor[1], currentColor[2]);
		for (int i = 0; i < 3; i++)
		{
			currentColor[i] = currentColor[i] + (rand() % 100 * 0.001f);
			currentColor[i] = currentColor[i] - (rand() % 100 * 0.001f);
			if (currentColor[i] < 0)
			{	
				currentColor[i] = 2;
			}
			else if (currentColor[i] > 255)
			{
				currentColor[i] = 253;
			}
		}
		
		MSG messages;
		while (window->Update(messages))
		{
			if (messages.message == WM_QUIT)
			{
				// Tuhotaan ikkuna, ei ole vielä koodattu.
			}
		}
		
		window->Clear();
		spriteBatch.Update();
		spriteBatch.Draw();
		window->Display();
	}

}


void Demo::TerminateScene()
{
	mobV.clear();
	spriteBatch.clearDrawables();
}
Demo::~Demo()
{
}
