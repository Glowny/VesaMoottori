#pragma once
#include "Sprite.h"


class Mob
{
public:
	Mob();
	Mob(Sprite *sprite);
	Mob(Sprite *sprite, bool enableAnimation);
	~Mob();
	Sprite *sprite;
	vector2f speed;

	bool animationEnabled;
	int currentFrameX;
	int currentFrameY;

	void CheckBoundaries();
	void Update();
	void ChangeFrame();
};

