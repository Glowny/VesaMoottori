#pragma once
#include "Sprite.h"
#include "Texture.h"
#include "vector2.h"
struct Drawable
{
	Drawable()
	{
		drawOrder = 0;
		sprite = NULL;
		texture = NULL;
		glPosition = vector2f(0.0f, 0.0f);
	}

	int drawOrder;
	vector2f glPosition;
	Sprite *sprite;
	Texture *texture;
};