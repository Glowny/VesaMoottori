#include "DemoToni.h"
DemoToni::DemoToni()
{
	LoadResources();
	InitShaders();
//	InitSpriteBatches();
}

void DemoToni::LoadResources()
{
	resourceManager.LoadShader("vertexShader.txt", "vertex");
	resourceManager.LoadShader("fragmentShader.txt", "fragment");

	resourceManager.CreateTexture("dnld.png", "dolan");
}

void DemoToni::InitShaders()
{
	shader.AddShader(resourceManager.FindShader("vertex"), GL_VERTEX_SHADER);
	shader.AddShader(resourceManager.FindShader("fragment"), GL_FRAGMENT_SHADER);
	shader.LinkProgram();

	shader.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	shader.AddVertexAttribPointer("attrColor", 3, 7, 2);
	shader.AddVertexAttribPointer("textPosition", 2, 7, 5);
}

void DemoToni::InitSpriteBatches()
{
	spriteBatch = SpriteBatch(*window);
	spriteBatch.SetShaderProgram(shader);
}

void DemoToni::SceneToni()
{
	//DeMOTONI
	vector2f _speed = vector2f(0, 0);
	bool goup = true;
	bool godown = false;
	Sprite Dolan;

	Dolan.setTexture(resourceManager.FindTexture("dolan"));
	Dolan.setSize(vector2f(1000, 1000));
	Dolan.setPosition(vector2f(1500, 900));
	//DeMOTONI
	
	spriteBatch.AddSprite(Dolan, 1);


	//While loop

	//DeMOTONI
	_speed.y -= 0.010;
	if (Dolan.getPosition().y > 300 && goup)
	{
		Dolan.setPosition(vector2f(Dolan.getPosition().x + _speed.x, Dolan.getPosition().y + _speed.y));
	}
	else
	{
		Dolan.setPosition(vector2f(Dolan.getPosition().x + _speed.x, Dolan.getPosition().y - _speed.y));
	}
	//DeMOTONI

	//



	window->Clear();
	spriteBatch.Draw();
	window->Display();

}


void DemoToni::TerminateScene()
{
}
DemoToni::~DemoToni()
{
}
