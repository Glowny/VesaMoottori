#pragma once
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Drawable.h"
#include "ShaderProgram.h"
#include "GraphicsDevice.h"
#include "vector2.h"

class SpriteBatch
{
public:
	SpriteBatch();
	SpriteBatch(GraphicsDevice &window);

	void Draw();

	void AddSprite(Sprite &sprite);
	void AddSprite(Sprite &sprite, int order);
	void AddTexture(Texture &texture);
	void AddTexture(Texture &texture, int order);

	void AddShaderProgram(ShaderProgram &shaderProgram);

	void SetDevice(GraphicsDevice &window);

	~SpriteBatch() {};

private:
	void Sort();
	std::vector<Drawable>::iterator FindLocation(int order);

	std::vector<Drawable> drawables;
	ShaderProgram *shaderProgram;
	GraphicsDevice *graphicsDevice;
	bool changes;
	vector2f size;

	//void SetMaxOrder();
	//void CheckMaxOrder(int newOrder);
	//int maxOrder;
	//std::vector<Texture> textures;
	//std::vector<Sprite> sprites;
};