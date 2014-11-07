#pragma once
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Drawable.h"
#include "ShaderProgram.h"
#include "GraphicsDevice.h"

class SpriteBatch
{
public:
	SpriteBatch();

	void AddSprite(Sprite &sprite);
	void AddSprite(Sprite &sprite, int order);
	void AddTexture(Texture &texture);
	void AddTexture(Texture &texture, int order);

	void AddShaderProgram(ShaderProgram &shaderProgram);

	void SetDevice(GraphicsDevice &window);

	void SetMaxOrder();
	

	void Draw();

	~SpriteBatch() {};

private:
	std::vector<Drawable> drawables;
	ShaderProgram *shaderProgram;
	GraphicsDevice *graphicsDevice;

	void Sort();
	void CheckMaxOrder(int newOrder);

	bool changes;
	int maxOrder;

	//std::vector<Texture> textures;
	//std::vector<Sprite> sprites;
};