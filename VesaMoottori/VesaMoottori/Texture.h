#pragma once
#include <GL\glew.h>
#include "Image.h"
#include "vector2.h"

class Texture
{
	// Texture luokkaa ei voi t‰ll‰ hetkell‰ k‰ytt‰‰ itsess‰‰n.
	// Ainoastaan ResourceManagerin kautta.
	friend class ResourceManager;

public:
	GLuint GetIndex();
	vector2f GetSize();
	~Texture();

private:
	Texture() : textureIndex(0), image(NULL) {};
	Texture(Image *image);
	GLuint textureIndex;
	Image *image;
};