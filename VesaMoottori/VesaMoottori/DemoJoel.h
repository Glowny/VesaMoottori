#pragma once
#include "Mob.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "ShaderProgram.h"
#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include <Time.h>
#include <vector>
class DemoJoel
{
public:
	DemoJoel();
	~DemoJoel();
	void SceneOne();
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
	std::vector<Mob> mobH;
};

