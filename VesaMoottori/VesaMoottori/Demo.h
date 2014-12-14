#pragma once
#include "Mob.h"
#include "SpriteBatch.h"
#include "ShaderProgram.h"
#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include <vector>

class Demo
{
public:
	Demo();
	~Demo() {};

	void SceneOne();
	void SceneTwo();
	void TuukkaScene();
	void TerminateScene();

private:
	void LoadResources();
	void InitShaders();
	void InitSpriteBatches();
	GraphicsDevice *window;
	ResourceManager resourceManager;
	ShaderProgram shader;
	SpriteBatch spriteBatch;
	Keyboard keyboard;
	std::vector<Mob> mobV;
	Keyboard Keys;
};

