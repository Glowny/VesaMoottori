#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "ShaderProgram.h"
#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "Keyboard.h"

class DemoTuukka
{
public:
	DemoTuukka() : running(true) {};
	~DemoTuukka() {};
	void TuukkaScene();
	void CloseScene() { running = false; }

private:
	bool running;
	ResourceManager R;
	Keyboard Keyboard;
};