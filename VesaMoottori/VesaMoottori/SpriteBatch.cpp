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
	if (changes)
	{
		Sort(); // Sortataan ennen buffereiden tekoa.
		CreateBuffer();
		changes = false;
	}
	// en oo ihan varma t‰st‰, tarviiko ilman muutoksia n‰it‰ bindata uusiksi.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	//
	if(shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// K‰ynnistet‰‰n default shaderi.
	}
}
void SpriteBatch::CreateBuffer()
{
	//asetetaan buffereihin oikea piirtoj‰rjestys.
	for (std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		if (it->sprite != NULL)
		{
			for (int i = 0; it->sprite->getIndexSize(); i++)
			{
				indexPointers.push_back(&it->sprite->getIndexPointer()[i]);
			}
			for (int i = 0; it->sprite->getVertexSize(); i++)
			{
				vertexPointers.push_back(&it->sprite->getVertexPointer()[i]);
			}
		}
	}

	glGenBuffers(2, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexPointers.size(), vertexPointers[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPointers.size(), indexPointers[0], GL_STATIC_DRAW);

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

	for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		// Sortataan piirrett‰v‰t orderin mukaan.
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

SpriteBatch::~SpriteBatch()
{
	// TERMINATE EVERYTHING
}