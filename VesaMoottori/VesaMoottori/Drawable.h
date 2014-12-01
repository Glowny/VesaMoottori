#pragma once
#include "Sprite.h"
#include "vector2.h"
struct Drawable
{
	Drawable()
	{
		drawOrder = 0;
		sprite = NULL;
	}

	int drawOrder;
	Sprite *sprite;

	//vector2f glPosition; Ei tarvita en‰‰.
};