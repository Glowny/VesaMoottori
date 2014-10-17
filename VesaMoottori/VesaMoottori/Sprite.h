#pragma once
#include "vector2i.h"
#include <vector>
#include "GL\glew.h"
class Sprite
{
public:
	Sprite(std::vector<unsigned char> decodedTexture, vector2i textureSize);

	std::vector<unsigned char> getTexture();
	vector2i getTextureSize();

	void setPosition(vector2i);
	vector2i getPosition();

	void setSourceRPosition(vector2i position);
	vector2i getSourceRPosition();

	void setSourceRSize(vector2i size);
	vector2i getSourceRSize();

	void setOrigin(vector2i origin);
	vector2i getOrigin();
	
	void setColorRGB(float red, float blue, float green);

	float getColorR();
	float getColorG();
	float getColorB();
	GLfloat* getVertexData();
	// ROTATE?
	~Sprite();
private:
	std::vector<unsigned char> _texture;
	vector2i _textureSize;
	vector2i _position;

	vector2i _sourceRectSize;
	vector2i _sourceRectPosition;
	vector2i _origin;
	float _red, _blue, _green;
	GLfloat VERTEX_DATA[28];
	// Width, height, x ja y:tä korvaamaan voisi tehdä vector2 tyyppisen olion.

};

