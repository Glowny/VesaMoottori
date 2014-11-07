#pragma once
#include "Sprite.h"
#include "Texture.h"
struct Drawable
{
	Drawable()
	{
		drawOrder = 0;
		sprite = NULL;
		texture = NULL;
	}

	int drawOrder;
	Sprite *sprite;
	Texture *texture;
};