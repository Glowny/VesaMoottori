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
	
	resourceManager.CreateTexture("BigSpaceGun.png", "Space");
	resourceManager.CreateTexture("Animation.png", "Animation"); 
	resourceManager.CreateTexture("exp2.png", "Explosion");
	resourceManager.CreateTexture("goofy.png", "goofy");
	resourceManager.CreateTexture("gooby.png", "gooby");
}

void Demo::InitShaders()
{
	shader.AddShader(resourceManager.FindShader("vertex"), GL_VERTEX_SHADER);
	shader.AddShader(resourceManager.FindShader("fragment"), GL_FRAGMENT_SHADER);
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

void Demo::SceneOne()
{
	srand(time(NULL));
	Sprite animation, resize, colorChange, animation_and_resize;

	animation.setTexture(resourceManager.FindTexture("Animation"));
	animation.setSourceRSize(vector2f(64.0f, 64.0f));
	animation.setSize(vector2f(70, 70));

	animation_and_resize.setTexture(resourceManager.FindTexture("Animation"));
	animation_and_resize.setSourceRSize(vector2f(64.0f, 64.0f));
	animation_and_resize.setSize(vector2f(10.0f, 10.0f));

	resize.setTexture(resourceManager.FindTexture("goofy"));
	resize.setSize(vector2f(500, 500));
	resize.setPosition(vector2f(400, 400));
	colorChange.setTexture(resourceManager.FindTexture("goofy"));
	colorChange.setSize(vector2f(250, 250));
	colorChange.setPosition(vector2f(600, 600));

	spriteBatch.AddSprite(animation, 0);
	spriteBatch.AddSprite(resize, 0);
	spriteBatch.AddSprite(animation_and_resize, 0);
	spriteBatch.AddSprite(colorChange, 0);

	mobV.push_back(Mob(&animation, true));
	mobV.push_back(Mob(&resize));
	mobV.push_back(Mob(&animation_and_resize, true));
	mobV.push_back(Mob(&colorChange));

	for (int i = 0; i < 10; i++)
	{
		Sprite* sprite = new Sprite;
		sprite->setTexture(resourceManager.FindTexture("goofy"));
		sprite->setSize(vector2f(50.0f * (i % 5), 50.0f * (i % 5)));
		sprite->setPosition(vector2f(500, 500));
		spriteBatch.AddSprite(*sprite, 3);
		mobV.push_back(sprite);
	}
	float sizeMultipler = 1;
	bool dir = true;
	float currentColor[3]{100, 200, 255};

	while (window->IsOpen())	// T�h�n joku toinen quittiehto.
	{
		resize.setSize(vector2f(sizeMultipler * 400, sizeMultipler * 400));
		animation_and_resize.setSize(vector2f(sizeMultipler * 400, sizeMultipler * 400));
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

		if (dir)
		{
			sizeMultipler = sizeMultipler + 0.007f;
		}
		else
		{
			sizeMultipler = sizeMultipler - 0.007f;
		}
		if (sizeMultipler > 1)
		{
			dir = false;

		}
		else if (sizeMultipler < 0)
		{
			dir = true;

		}

		colorChange.setColorRGB(currentColor[0], currentColor[1], currentColor[2]);
		animation_and_resize.setColorRGB(currentColor[1], currentColor[2], currentColor[0]);
		for (int i = 0; i < 3; i++)
		{
			currentColor[i] = currentColor[i] + (rand() % 100 * 0.3f);
			currentColor[i] = currentColor[i] - (rand() % 100 * 0.3f);
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
				// Tuhotaan ikkuna, ei ole viel� koodattu.
			}
		}
		
		window->Clear();
		spriteBatch.Draw();
		window->Display();
	}

}



void Demo::SceneTwo()
{
	srand(time(NULL));

	while (window->IsOpen())	// T�h�n joku toinen quittiehto.
	{
		Sprite* sprite = new Sprite();
		sprite->setTexture(resourceManager.FindTexture("BigSpaceGun.png"));
		sprite->setSourceRPosition(vector2f(64.0f, 64.0f));
		sprite->setSourceRSize(vector2f(64.0f, 64.0f));
		sprite->setSize(vector2f(96.0f, 96.0f));

		
		MSG messages;
		while (window->Update(messages))
		{
			if (messages.message == WM_QUIT)
			{
				// Tuhotaan ikkuna, ei ole viel� koodattu.
			}
		}

		window->Clear();
		spriteBatch.Draw();
		window->Display();
	}

	
}

void Demo::TerminateScene()
{
	mobV.clear();
	spriteBatch.ClearDrawables();
}
Demo::~Demo()
{
}
