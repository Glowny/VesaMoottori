#pragma once
#include "VesaMoottori\Sprite.h"


class Mob
{
public:
	Mob();
	Mob(Sprite *sprite);
	~Mob();
	Sprite *sprite;
	vector2f speed;

	void CheckBoundaries();
	void Update();
};

