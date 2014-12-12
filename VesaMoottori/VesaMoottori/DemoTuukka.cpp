#include "DemoTuukka.h"

DemoTuukka::DemoTuukka()
{
	window = new GraphicsDevice("Demo", 1800, 1200);
	LoadResources();
	InitShaders();
	InitSpriteBatches();
}

void DemoTuukka::LoadResources()
{
	resourceManager.LoadShader("vertexShader.txt", "vertex");
	resourceManager.LoadShader("fragmentShader.txt", "fragment");

	resourceManager.CreateTexture("Animation.png", "Animation"); 
	resourceManager.CreateTexture("exp2.png", "Explosion");
	resourceManager.CreateTexture("goofy.png", "goofy");
	resourceManager.CreateTexture("gooby.png", "gooby");
}

void DemoTuukka::InitShaders()
{
	shader.AddShader(resourceManager.FindShader("vertex"), GL_VERTEX_SHADER);
	shader.AddShader(resourceManager.FindShader("fragment"), GL_FRAGMENT_SHADER);
	shader.LinkProgram();

	shader.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	shader.AddVertexAttribPointer("attrColor", 3, 7, 2);
	shader.AddVertexAttribPointer("textPosition", 2, 7, 5);
}

void DemoTuukka::InitSpriteBatches()
{
	spriteBatch = SpriteBatch(*window);
	spriteBatch.SetShaderProgram(shader);
}

void DemoTuukka::TuukkaScene()
{

}

void DemoTuukka::TerminateScene()
{
}

DemoTuukka::~DemoTuukka()
{
}