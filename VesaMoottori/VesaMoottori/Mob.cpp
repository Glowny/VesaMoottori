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

Mob::Mob(Sprite *sprite, bool enableAnimation)
{
	this->sprite = sprite;
	animationEnabled = enableAnimation;
	speed = vector2f(0, 0);
	currentFrameX = 0;
	currentFrameY = 0;
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
	if (location.x >= 1600.0f)
	{
		speed.x = (speed.x - 0.2f)*0.9f;

	}
	else if (location.x <= 0.0f)
	{
		speed.x = (speed.x + 0.2f)*0.9f;

	}
	if (location.y >= 1200.0f)
	{
		speed.y = (speed.y - 0.2f)*0.9f;

	}
	else if (location.y <= 0.0f)
	{
		speed.y = (speed.y + 0.2f)*0.9f;


	}
}

void Mob::ChangeFrame()
{
	
	sprite->setSourceRPosition(vector2f(currentFrameX*sprite->getSourceRSize().x, currentFrameY*sprite->getSourceRSize().y));
	currentFrameX++;
	if (currentFrameX > 3)
	{
		currentFrameX = 0;
		currentFrameY++;
	}
	if (currentFrameY > 3)
	{
		currentFrameY = 0;
	}
}