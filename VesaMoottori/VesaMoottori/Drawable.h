#pragma once
#include "Sprite.h"
#include "vector2.h"
struct Drawable
{
	Drawable()
	{
		drawOrder = 0;
		sprite = NULL;
		glPosition = vector2f(0.0f, 0.0f);
	}

	int drawOrder;
	vector2f glPosition;
	Sprite *sprite;
};