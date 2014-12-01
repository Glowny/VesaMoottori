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

	// Nämä tulee myöhemmin.
	//void Update();
	//void SetSize(); 
	//void SetPosition();

private:
	void Sort(); // Pitää piirrot järjestyksessä.
	std::vector<Drawable>::iterator FindLocation(int order); // Iteraattori help-funktio.
	void CreateBuffers();

	GLuint arrayBuffer;
	GLuint elementArrayBuffer;

	std::vector<Drawable> drawables;
	ShaderProgram *shaderProgram;
	GraphicsDevice *graphicsDevice;
	vector2f size;

	/*
	//void purkkaChanges() { changes = true; }
	std::vector<GLuint> indexPointers;
	std::vector<GLfloat*> vertexPointers;
	GLuint buffer[2];
	void CreateBuffer();
	bool changes;

	void addSprite(GLuint* indexPointer, GLsizei indexSize, GLfloat* vertexPointer, GLsizei vertexSize) // tai vain sprite ja siitä repii noi irti.
	{
	for (int i = 0; i < indexSize; i++)
	{
	indexPointers.push_back(&indexPointer[i]);
	}
	for (int i = 0; i < vertexSize; i++)
	{
	vertexPointers.push_back(&vertexPointer[i]);
	}
	}
	void createBuffer()
	{
	glGenBuffers(2, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexPointers.size(), vertexPointers[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPointers.size(), indexPointers[0], GL_STATIC_DRAW);
	}
	*/
};
