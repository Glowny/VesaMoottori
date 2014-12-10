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

	void Update();
	void Draw();

	void AddSprite(Sprite &sprite);
	void AddSprite(Sprite &sprite, int order);

	void purkkaChanges()
	{
		changes = true;
	}

	void SetShaderProgram(ShaderProgram &shaderProgram);
	void SetDevice(GraphicsDevice &window);

private:
	void Sort(); // Pit‰‰ piirrot j‰rjestyksess‰.
	vector2f TextureToGLCoord(float x, float y);
	vector2f PositionToGlCoord(float x, float y);
	GLfloat ColorToGLCoord(GLfloat x);

	std::vector<Drawable>::iterator FindLocation(int order); // Iteraattori help-funktio.

	std::vector<Drawable> drawables;
	ShaderProgram *shaderProgram;
	GraphicsDevice *graphicsDevice;
	bool changes;
	vector2f size;
	std::vector<GLuint> indexData;
	std::vector<GLfloat> vertexData;
	GLuint buffer[2];
	void CreateBuffer();

	/*


	void addSprite(GLuint* indexPointer, GLsizei indexSize, GLfloat* vertexPointer, GLsizei vertexSize) // tai vain sprite ja siit‰ repii noi irti.
	{
	for (int i = 0; i < indexSize; i++)
	{
	indexData.push_back(&indexPointer[i]);
	}
	for (int i = 0; i < vertexSize; i++)
	{
	vertexPointers.push_back(&vertexPointer[i];)
	}
	}
	void createBuffer()
	{
	glGenBuffers(2, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexPointers.size(), vertexPointers[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size(), indexData[0], GL_STATIC_DRAW);
	}
	*/
};
