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
	void ClearDrawables();

	void SetShaderProgram(ShaderProgram &shaderProgram);
	void SetDevice(GraphicsDevice &window);

	void UnbindBuffers(); // !!! MUISTA SIIRT�� TAKASIN PRIVATEKSI
private:
	void Update();
	void Sort(); // Pit�� piirrot j�rjestyksess�.
	vector2f TextureToGLCoord(float x, float y, vector2f spriteSize);
	vector2f PositionToGlCoord(float x, float y);
	GLfloat ColorToGLCoord(GLfloat x);
	void CreateBuffer();

	std::vector<Drawable>::iterator FindLocation(int order); // Iteraattori help-funktio.

	std::vector<Drawable>	drawables;
	ShaderProgram			*shaderProgram;
	GraphicsDevice			*graphicsDevice;
	bool					changes;
	vector2f				size;
	std::vector<GLuint>		indexData;
	std::vector<GLfloat>	vertexData;
	GLuint					buffer[2];
};