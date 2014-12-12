#pragma once
#include "Mob.h"
#include "VesaMoottori\Texture.h"
#include "VesaMoottori\Sprite.h"
#include "VesaMoottori\SpriteBatch.h"
#include "VesaMoottori\ShaderProgram.h"
#include "VesaMoottori\GraphicsDevice.h"
#include "VesaMoottori\ResourceManager.h"
#include "VesaMoottori\Keyboard.h"


#include <Time.h>
#include <vector>
class Demo
{
public:
	Demo();
	~Demo();
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
};

