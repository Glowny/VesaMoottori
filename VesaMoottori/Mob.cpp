#include "Mob.h"


Mob::Mob()
{
	speed = vector2f(0, 0);
}
Mob::Mob(Sprite *sprite)
{
	this->sprite = sprite;
	speed = vector2f(0, 0);
}

Mob::~Mob()
{
}

void Mob::Update()
{
	CheckBoundaries();
	sprite->setPosition(vector2f(sprite->getPosition().x + speed.x, sprite->getPosition().y + speed.y));
}
void Mob::CheckBoundaries()
{
	vector2f location = sprite->getPosition();
	if (location.x > 1.0f)
	{
		speed.x = speed.x * -0.9f;
	}
	else if (location.x < -1.0f)
	{
		speed.x = speed.x * -0.9f;
	}
	if (location.y > 1.0f)
	{
		speed.y = speed.y * -0.9f;
	}
	else if (location.y < -1.0f)
	{
		speed.y =speed.y * -0.9f;
	}
}