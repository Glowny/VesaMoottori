#pragma once
#include "vector2i.h"
#include <vector>
#include "GL\glew.h"
#include "Image.h"
class Sprite
{
public:
	Sprite();

	void setImage(Image *img);
	// VAI getImage?;
	std::vector<unsigned char> getTexture();
	vector2f getTextureSize();

	void setPosition(vector2f);
	vector2f getPosition();

	void setSourceRPosition(vector2f position);
	vector2f getSourceRPosition();

	void setSourceRSize(vector2f size);	// näille pitää keksiä joku käyttö
	vector2f getSourceRSize();

	void setOrigin(vector2f origin);
	vector2f getOrigin();
	
	void setColorRGB(float red, float blue, float green);

	float getColorR();
	float getColorG();
	float getColorB();

	GLfloat* getVertexData();
	GLuint* getIndexData();
	// ROTATE?
	~Sprite();
private:

	Image _image;
	vector2f _position;
	vector2f _sourceRectSize;
	vector2f _sourceRectPosition;
	vector2f _origin;
	float _red, _blue, _green;


	GLfloat VERTEX_DATA[28];
	GLuint INDEX_DATA[6];
};

