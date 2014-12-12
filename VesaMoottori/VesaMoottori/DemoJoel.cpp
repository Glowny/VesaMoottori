#include "DemoJoel.h"

DemoJoel::DemoJoel()
{
	window = new GraphicsDevice("Demo", 1800, 1200);
	LoadResources();
	InitShaders();
	InitSpriteBatches();
}

void DemoJoel::LoadResources()
{
	resourceManager.LoadShader("vertexShader.txt", "vertex");
	resourceManager.LoadShader("fragmentShader.txt", "fragment");

	resourceManager.CreateTexture("Walking.png", "Walker");
	resourceManager.CreateTexture("Enemy.png", "Enemy");
}

void DemoJoel::InitShaders()
{
	shader.AddShader(resourceManager.FindShader("vertex"), GL_VERTEX_SHADER);
	shader.AddShader(resourceManager.FindShader("fragment"), GL_FRAGMENT_SHADER);
	shader.LinkProgram();

	shader.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	shader.AddVertexAttribPointer("attrColor", 3, 7, 2);
	shader.AddVertexAttribPointer("textPosition", 2, 7, 5);
}

void DemoJoel::InitSpriteBatches()
{
	spriteBatch = SpriteBatch(*window);
	spriteBatch.SetShaderProgram(shader);
}

void DemoJoel::SceneOne()
{
	int enemyCount = 0;
	Sprite hero;
	Sprite* Enemy = new Sprite;
	hero.setTexture(resourceManager.FindTexture("Walker"));
	hero.setSourceRSize(vector2f(125.0f, 125.0f));
	hero.setPosition(vector2f(600, 600));

	spriteBatch.AddSprite(hero, 0);

	mobH.push_back(Mob(&hero, true));


	//if (hero.getPosition().x < zombi.getPosition().x)
	//{ }
	//if (hero.getPosition().x > zombi.getPosition().x)
	//{ zombi.}

	while (window->IsOpen())	// Tähän joku toinen quittiehto.
	{
		if (enemyCount == 0)
		{
			for (enemyCount; enemyCount < 6; enemyCount++)
			{
				
				Enemy->setTexture(resourceManager.FindTexture("Enemy"));
				Enemy->setSourceRSize(vector2f(128, 128));
				int random = rand() % 3;

				if (random == 1)
					Enemy->setPosition(vector2f(1800, 800));

				else
					Enemy->setPosition(vector2f(0, 800));

				spriteBatch.AddSprite(*Enemy, 1);
				mobV.push_back(Enemy);
			}
		}

		for (unsigned i = 0; i < mobV.size(); i++)
		{
			if (hero.getPosition().x < Enemy->getPosition().x)
				mobV[i].speed.x = mobV[i].speed.x++;

			if (hero.getPosition().x > Enemy->getPosition().x)
				mobV[i].speed.x = mobV[i].speed.x--;

			mobV[i].Update();
			if (mobV[i].animationEnabled == true)
			{
				mobV[i].ChangeFrame();
			}

		}
		mobH[0].Update();

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


void DemoJoel::TerminateScene()
{
	mobV.clear();
	spriteBatch.ClearDrawables();
}
DemoJoel::~DemoJoel()
{
}
