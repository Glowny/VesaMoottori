#include "VesaMoottori\DemoToni.h"
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
	Sprite Dolan;

	Dolan.setTexture(resourceManager.FindTexture("dolan"));
	Dolan.setSourceRSize(vector2f(64.0f, 64.0f));
	Dolan.setSize(vector2f(100, 100));

	spriteBatch.AddSprite(Dolan, 0);

	Dolan.setPosition(vector2f(500, 500));

	window->Clear();
	spriteBatch.Update();
	spriteBatch.Draw();
	window->Display();

}


void DemoToni::TerminateScene()
{
}
DemoToni::~DemoToni()
{
}
