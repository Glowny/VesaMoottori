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
	~SpriteBatch();

	void Draw();

	void AddSprite(Sprite &sprite);
	void AddSprite(Sprite &sprite, int order);

	void SetShaderProgram(ShaderProgram &shaderProgram);
	void SetDevice(GraphicsDevice &window);

private:
	void Sort(); // Pit‰‰ piirrot j‰rjestyksess‰.
	std::vector<Drawable>::iterator FindLocation(int order); // Iteraattori help-funktio.

	std::vector<Drawable> drawables;
	ShaderProgram *shaderProgram;
	GraphicsDevice *graphicsDevice;
	bool changes;
	vector2f size;
};