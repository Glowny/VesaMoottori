#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "ShaderProgram.h"
#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include <Time.h>
#include <vector>

class DemoTuukka
{
public:
	DemoTuukka();
	~DemoTuukka();
	void TuukkaScene();
	void TerminateScene();

private:
	void LoadResources();
	void InitShaders();
	void InitSpriteBatches();

	GraphicsDevice		*window;
	ResourceManager		resourceManager;
	ShaderProgram		shader;
	SpriteBatch			spriteBatch;
	Keyboard			keyboard;
};