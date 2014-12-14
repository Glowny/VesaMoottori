#include "Demo.h"
#include "Sprite.h"
#include <Time.h>

Demo::Demo()
{
	window = new GraphicsDevice("Demo", 1600, 1200);
	LoadResources();
	InitShaders();
	InitSpriteBatches();
}

void Demo::LoadResources()
{
	resourceManager.LoadShader("vertexShader.txt", "vertex");
	resourceManager.LoadShader("fragmentShader.txt", "fragment");

	resourceManager.CreateTexture("zombies.png", "Zombies");
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
	// Scene: testataan mill‰ m‰‰r‰ll‰ spritej‰ fps tippuu
	// Input:
	// R - toggle spritespawn
	// A - Spawn 50 sprites


	srand((unsigned int)time(NULL));
	Sprite animation, resize, colorChange, animation_and_resize, sprite_static;

	sprite_static.setPosition(vector2f(100, 200));
	sprite_static.setTexture(resourceManager.FindTexture("goofy"));
	sprite_static.setSize(vector2f(200, 200));
	spriteBatch.AddSprite(sprite_static);

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
	bool dir = true, running = true;;
	float currentColor[3]{100, 200, 255};

	srand((unsigned int)time(NULL));
	bool spawn = false;

	while (running)	// T‰h‰n joku toinen quittiehto.
	{
		if (spawn == true)
		{
			Sprite* sprite = new Sprite();
			sprite->setTexture(resourceManager.FindTexture("Zombies"));
			sprite->setSourceRPosition(vector2f(3.0f, 10.0f));
			sprite->setSourceRSize(vector2f(24.0f, 32.0f));
			sprite->setSize(vector2f(128.0f, 128.0f));
			sprite->setPosition(vector2f((float)(rand() % 1800), (float)(rand() % 1200)));
			spriteBatch.AddSprite(*sprite, 0);
			mobV.push_back(Mob(sprite, 0));
		}

		for (unsigned i = 0; i < mobV.size(); i++)
		{
			mobV[i].speed.x = mobV[i].speed.x + ((rand() % 100) * 0.001f);
			mobV[i].speed.x = mobV[i].speed.x - ((rand() % 100) * 0.001f);
			mobV[i].speed.y = mobV[i].speed.y + ((rand() % 100) * 0.001f);
			mobV[i].speed.y = mobV[i].speed.y - ((rand() % 100) * 0.001f);

			mobV[i].Update();

		}

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
				// Tuhotaan ikkuna, ei ole viel‰ koodattu.
			}
			if (Keys.isKeyPressed(Keys.Key::A))
			{
				for (int i = 0; i < 100; i++)
				{
					Sprite* sprite = new Sprite();
					sprite->setTexture(resourceManager.FindTexture("Zombies"));
					sprite->setSourceRPosition(vector2f(3.0f, 10.0f));
					sprite->setSourceRSize(vector2f(24.0f, 32.0f));
					sprite->setSize(vector2f(128.0f, 128.0f));
					sprite->setPosition(vector2f((float)(rand() % 1800), (float)(rand() % 1200)));
					spriteBatch.AddSprite(*sprite, 0);
					mobV.push_back(Mob(sprite, 0));
				}
			}
			if(Keys.isKeyPressed(Keys.Key::S))
				running = false;
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

void Demo::TuukkaScene()
{
	//GraphicsDevice Ikkuna("Tuukka", 1024, 768);
	SpriteBatch BG(*window);
	SpriteBatch Game(*window);
	SpriteBatch UI(*window);

	resourceManager.CreateTexture("BG0.png", "BGFar");
	resourceManager.CreateTexture("BG1.png", "BGMid");
	resourceManager.CreateTexture("BG2.png", "BGClose");
	resourceManager.CreateTexture("Hahmo.png", "Hahmo");
	resourceManager.CreateTexture("UI.png", "UI");
	resourceManager.CreateTexture("TuukkaScene.png", "Scene");

	ShaderProgram ShaderProg;
	ShaderProg.AddShader(resourceManager.LoadShader("TuukkaVertex.txt", "VERTEX_SHADER"), GL_VERTEX_SHADER);
	ShaderProg.AddShader(resourceManager.LoadShader("TuukkaFragment.txt", "FRAGMENT_SHADER"), GL_FRAGMENT_SHADER);
	ShaderProg.LinkProgram();

	ShaderProg.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	ShaderProg.AddVertexAttribPointer("attrColor", 3, 7, 2);
	ShaderProg.AddVertexAttribPointer("textPosition", 2, 7, 5);

	BG.SetShaderProgram(ShaderProg);
	Game.SetShaderProgram(ShaderProg);
	UI.SetShaderProgram(ShaderProg);

	Sprite BG_FAR, BG_FAR2, BG_MID, BG_CLOSE, CHARACTER, BG_UI, SCENE;
	BG_FAR.setTexture(resourceManager.FindTexture("BGFar"));
	BG_FAR2.setTexture(resourceManager.FindTexture("BGFar"));
	BG_MID.setTexture(resourceManager.FindTexture("BGMid"));
	BG_CLOSE.setTexture(resourceManager.FindTexture("BGClose"));
	CHARACTER.setTexture(resourceManager.FindTexture("Hahmo"));
	BG_UI.setTexture(resourceManager.FindTexture("UI"));
	SCENE.setTexture(resourceManager.FindTexture("Scene"));

	vector2f IKKUNA_SIZE = vector2f((float)window->GetSize().x, (float)window->GetSize().y);
	//vector2f NOLLA_PISTE = vector2f((float)window->GetSize().x, 0); // Miksi nollapiste on oikeassa-yl‰kulmassa?
	vector2f NOLLA_PISTE = vector2f(0.0f, 0.0f); // Helpoin tapa fixata demo.
	BG_FAR.setSize(IKKUNA_SIZE);
	BG_FAR.setPosition(NOLLA_PISTE);
	BG_FAR2.setSize(IKKUNA_SIZE);
	BG_FAR2.setPosition(vector2f(NOLLA_PISTE.x - BG_FAR2.getSize().x, NOLLA_PISTE.y));
	BG_MID.setSize(IKKUNA_SIZE);
	BG_MID.setPosition(NOLLA_PISTE);
	BG_CLOSE.setSize(IKKUNA_SIZE);
	BG_CLOSE.setPosition(NOLLA_PISTE);
	BG.AddSprite(BG_FAR, 0);
	BG.AddSprite(BG_FAR2, 0);
	BG.AddSprite(BG_MID, 1);
	//BG.AddSprite(BG_CLOSE, 2);

	float CHARACTER_SIZE_MODIFIER = 4.0f;
	int SPRITE_FRAMES = 3;
	vector2f FRAME_SIZE = vector2f(resourceManager.FindTexture("Hahmo")->GetSize().x / (float)SPRITE_FRAMES, resourceManager.FindTexture("Hahmo")->GetSize().y);
	CHARACTER.setSize(FRAME_SIZE * CHARACTER_SIZE_MODIFIER);
	CHARACTER.setSourceRSize(FRAME_SIZE);
	CHARACTER.setPosition(NOLLA_PISTE - vector2f(100, -300));
	Game.AddSprite(CHARACTER);

	vector2f UI_SIZE = resourceManager.FindTexture("UI")->GetSize();
	vector2f SCENE_SIZE = resourceManager.FindTexture("Scene")->GetSize();
	BG_UI.setSize(UI_SIZE);
	BG_UI.setOrigin(UI_SIZE * 0.5f);
	BG_UI.setPosition(vector2f(IKKUNA_SIZE.x * 0.5f, IKKUNA_SIZE.y * 0.82f));
	SCENE.setSize(SCENE_SIZE);
	SCENE.setOrigin(SCENE_SIZE * 0.5f);
	SCENE.setPosition(vector2f(IKKUNA_SIZE.x * 0.5f, IKKUNA_SIZE.y * 0.95f));
	UI.AddSprite(BG_UI);
	UI.AddSprite(SCENE);

	int i = 1, korkeus = 0;
	float korkeus_mod = 1.0f;

	while(true)
	{
		MSG MESSAGES;
		while(window->Update(MESSAGES))
		{
			//TO-DO: Message receives.
		}

		window->Clear();
		BG.Draw();
		BG.ChangeBatch();
		Game.Draw();
		Game.ChangeBatch();
		UI.Draw();
		UI.ChangeBatch();
		window->Display();

		vector2f characterPosition = CHARACTER.getPosition();
		if(korkeus < 10)
		{
			CHARACTER.setPosition(characterPosition + vector2f(4, (1 * korkeus_mod)));
			korkeus++;
		}
		else
		{
			korkeus = 0;
			if(korkeus_mod == 1.0f)
				korkeus_mod = -1.0f;
			else
				korkeus_mod = 1.0f;
		}

		vector2f cloudsPosition = BG_FAR.getPosition();
		vector2f cloudsPosition2 = BG_FAR2.getPosition();
		BG_FAR.setPosition(cloudsPosition + vector2f(5, 0));
		BG_FAR2.setPosition(cloudsPosition2 + vector2f(5, 0));
		if(i % 205 == 0)
			BG_FAR.setPosition(vector2f(NOLLA_PISTE.x - BG_FAR2.getSize().x, NOLLA_PISTE.y));

		i++;
		if(i > 400) // Timer scenen lopettamiseen.
			break;
	}

	// Jostain syyst‰ crashaa jos yritt‰‰ vaihtaa toiseen demoon.
	// Oisko ikkunan luomisessa/tuhoamisessa h‰ikk‰‰?
	//resourceManager.DeleteAll();
}