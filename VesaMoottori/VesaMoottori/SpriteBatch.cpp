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
	for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		if(it->sprite != NULL)
		{
			// Kumman kautta piirretään?
			//it->sprite->Draw()
			//graphicsDevice->Draw()
		}
		else if(it->texture != NULL)
		{
			// Texturen piirto-logiikka.
		}
		else
		{
			// Drawable korruptoitunut.
		}
	}


	shaderProgram->RunProgram();
}

void SpriteBatch::AddSprite(Sprite &sprite)
{
	Drawable temp;
	temp.drawOrder = 0;
	temp.sprite = &sprite;
	temp.texture = NULL;
	drawables.push_back(temp);
}

void SpriteBatch::AddSprite(Sprite &sprite, int order)
{
	Drawable temp;
	temp.drawOrder = order;
	temp.sprite = &sprite;
	temp.texture = NULL;
	drawables.insert(FindLocation(order), temp);
}

void SpriteBatch::AddTexture(Texture &texture)
{
	Drawable temp;
	temp.drawOrder = 0;
	temp.texture = &texture;
	temp.sprite = NULL;
	drawables.push_back(temp);
}

void SpriteBatch::AddTexture(Texture &texture, int order)
{
	Drawable temp;
	temp.drawOrder = order;
	temp.texture = &texture;
	temp.sprite = NULL;
	drawables.insert(FindLocation(order), temp);
}

void SpriteBatch::AddShaderProgram(ShaderProgram &shaderProgram)
{
	(this->shaderProgram) = &shaderProgram;
}

void SpriteBatch::SetDevice(GraphicsDevice &graphicsDevice)
{
	(this->graphicsDevice) = &graphicsDevice;
}

void SpriteBatch::Sort()
{
	for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		// Sortataan piirrettävät orderin mukaan.
		std::sort(drawables.begin(), drawables.end(),
			[](Drawable a, Drawable b){return (a.drawOrder > b.drawOrder); });
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

//void SpriteBatch::CheckMaxOrder(int order)
//{
//	if(order > maxOrder)
//		maxOrder = order;
//}