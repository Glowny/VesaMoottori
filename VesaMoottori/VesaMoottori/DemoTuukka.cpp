#include "DemoTuukka.h"
#include "SpriteBatch.h"
#include "ShaderProgram.h"

void DemoTuukka::TuukkaScene()
{
	GraphicsDevice Ikkuna("Tuukka", 1024, 768);
	SpriteBatch BG(Ikkuna);
	SpriteBatch Game(Ikkuna);
	SpriteBatch UI(Ikkuna);

	R.CreateTexture("BG0.png", "BGFar");
	R.CreateTexture("BG1.png", "BGMid");
	R.CreateTexture("BG2.png", "BGClose");
	R.CreateTexture("Hahmo.png", "Hahmo");
	R.CreateTexture("UI.png", "UI");

	ShaderProgram ShaderProg;
	ShaderProg.AddShader(R.LoadShader("TuukkaVertex.txt", "VERTEX_SHADER"), GL_VERTEX_SHADER);
	ShaderProg.AddShader(R.LoadShader("TuukkaFragment.txt", "FRAGMENT_SHADER"), GL_FRAGMENT_SHADER);
	ShaderProg.LinkProgram();

	ShaderProg.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	ShaderProg.AddVertexAttribPointer("attrColor", 3, 7, 2);
	ShaderProg.AddVertexAttribPointer("textPosition", 2, 7, 5);

	BG.SetShaderProgram(ShaderProg);
	Game.SetShaderProgram(ShaderProg);
	UI.SetShaderProgram(ShaderProg);

	Sprite BG_FAR, BG_FAR2, BG_MID, BG_CLOSE, CHARACTER, BG_UI;
	BG_FAR.setTexture(R.FindTexture("BGFar"));
	BG_FAR2.setTexture(R.FindTexture("BGFar"));
	BG_MID.setTexture(R.FindTexture("BGMid"));
	BG_CLOSE.setTexture(R.FindTexture("BGClose"));
	CHARACTER.setTexture(R.FindTexture("Hahmo"));
	BG_UI.setTexture(R.FindTexture("UI"));

	vector2f IKKUNA_SIZE = vector2f((float)Ikkuna.GetSize().x, (float)Ikkuna.GetSize().y);
	vector2f NOLLA_PISTE = vector2f((float)Ikkuna.GetSize().x, 0); // Miksi nollapiste on oikeassa-yl‰kulmassa?
	BG_FAR.setSize(IKKUNA_SIZE);
	BG_FAR.setPosition(NOLLA_PISTE);
	BG_FAR2.setSize(IKKUNA_SIZE);
	BG_FAR2.setPosition(vector2f(NOLLA_PISTE.x - BG_FAR2.getSize().x, NOLLA_PISTE.y));
	BG_MID.setSize(IKKUNA_SIZE);
	BG_MID.setPosition(NOLLA_PISTE);
	BG_CLOSE.setSize(IKKUNA_SIZE);
	BG_CLOSE.setPosition(NOLLA_PISTE);
	Game.AddSprite(BG_FAR, 0);
	Game.AddSprite(BG_FAR2, 0);
	Game.AddSprite(BG_MID, 1);
	Game.AddSprite(BG_CLOSE, 2);

	float CHARACTER_SIZE_MODIFIER = 4.0f;
	int SPRITE_FRAMES = 3;
	vector2f FRAME_SIZE = vector2f(R.FindTexture("Hahmo")->GetSize().x / (float)SPRITE_FRAMES, R.FindTexture("Hahmo")->GetSize().y);
	CHARACTER.setSize(FRAME_SIZE * CHARACTER_SIZE_MODIFIER);
	CHARACTER.setSourceRSize(FRAME_SIZE);
	CHARACTER.setPosition(NOLLA_PISTE - vector2f(100, -300));
	Game.AddSprite(CHARACTER);

	vector2f UI_SIZE = R.FindTexture("UI")->GetSize();
	BG_UI.setSize(UI_SIZE);
	BG_UI.setOrigin(UI_SIZE * 0.5f);
	BG_UI.setPosition(vector2f(IKKUNA_SIZE.x * 0.5f, IKKUNA_SIZE.y * 0.2f));
	UI.AddSprite(BG_UI);

	int i = 0, korkeus = 0;
	float korkeus_mod = 1.0f;

	while(running)
	{
		MSG MESSAGES;
		while(Ikkuna.Update(MESSAGES))
		{
			//TO-DO: Message receives.
		}

		Ikkuna.Clear();
		//BG.Draw();
		Game.Draw();
		//UI.Draw();
		Ikkuna.Display();

		vector2f characterPosition = CHARACTER.getPosition();
		if(korkeus < 10)
		{
			CHARACTER.setPosition(characterPosition + vector2f(-4, (1 * korkeus_mod)));
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

		if(cloudsPosition.x > IKKUNA_SIZE.x)
			BG_FAR.setPosition(NOLLA_PISTE);

		i++;
		if(i > 700) // Timer scenen lopettamiseen.
			break;
	}

	// Jostain syyst‰ crashaa jos yritt‰‰ vaihtaa toiseen demoon.
	// Oisko ikkunan luomisessa/tuhoamisessa h‰ikk‰‰?
	R.DeleteAll();
}