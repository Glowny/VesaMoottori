#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch()
{
	changes = true;
	size = vector2f(0.0f, 0.0f);
}

SpriteBatch::SpriteBatch(GraphicsDevice &window)
{
	changes = true;
	size = vector2f((float)window.GetWindowSize().x, (float)window.GetWindowSize().y);
}

void SpriteBatch::Draw()
{
	Sort(); // Sortataan ennen piirtoa.

	for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		if(it->sprite != NULL)
		{
			it->sprite->Draw();
		}
		else
		{
			// Drawable korruptoitunut.
		}
	}

	if(shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// Käynnistetään default shaderi.
	}
}

void SpriteBatch::AddSprite(Sprite &sprite)
{
	Drawable temp;
	temp.drawOrder = 0;
	temp.sprite = &sprite;
	drawables.push_back(temp);
}

void SpriteBatch::AddSprite(Sprite &sprite, int order)
{
	Drawable temp;
	temp.drawOrder = order;
	temp.sprite = &sprite;
	drawables.insert(FindLocation(order), temp);
}

void SpriteBatch::SetShaderProgram(ShaderProgram &shaderProgram)
{
	(this->shaderProgram) = &shaderProgram;
}

void SpriteBatch::SetDevice(GraphicsDevice &graphicsDevice)
{
	(this->graphicsDevice) = &graphicsDevice;
}

void SpriteBatch::Sort()
{
	if(changes)
	{
		for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
		{
			// Sortataan piirrettävät orderin mukaan.
			std::sort(drawables.begin(), drawables.end(),
				[](Drawable a, Drawable b){return (a.drawOrder > b.drawOrder); });
		}
		changes = false;
	}
}

std::vector<Drawable>::iterator SpriteBatch::FindLocation(int order)
{
	std::vector<Drawable>::iterator it;
	for(it = drawables.begin(); it != drawables.end(); it++)
	{
		if(it->drawOrder >= order)
			break;
	}
	return it;
}

SpriteBatch::~SpriteBatch()
{
	// TERMINATE EVERYTHING
}