#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch()
{
	changes = true;
	size = vector2f(0.0f, 0.0f);
	glGenBuffers(2, &buffer[0]);
}

SpriteBatch::SpriteBatch(GraphicsDevice &window)
{
	changes = true;
	size = vector2f((float)window.GetSize().x, (float)window.GetSize().y);
	(this->graphicsDevice) = &window;
	glGenBuffers(2, &buffer[0]);
	
}
void SpriteBatch::Update()
{
	if (changes)
	{
		Sort(); // Sortataan ennen buffereiden tekoa.
		CreateBuffer();
		changes = false;
	}
	for (int i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite->positionChanged)
			drawables[i].sprite->changePositionData(size); // jos halutaan pysy‰ windowin koossa, eik‰ spritebatchin koossa niin muutetaan graphicsdevice.getsize()

		if (drawables[i].sprite->texturePositionChanged)
			drawables[i].sprite->changeTexturePosition();

		if (drawables[i].sprite->colorChanged)
			drawables[i].sprite->changeColorData();
	}
}
void SpriteBatch::Draw()
{
	
	// en oo ihan varma t‰st‰, tarviiko ilman muutoksia n‰it‰ bindata uusiksi.
	// no jaa, tarvi tekstuurin jostaki
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	//
	if(shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// K‰ynnistet‰‰n default shaderi.
	}
	GLuint currentTextureIndex = -1;
	for (int i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite->texture->getTextureIndex() != currentTextureIndex)
		{
			currentTextureIndex = drawables[i].sprite->texture->getTextureIndex();
			glBindTexture(GL_TEXTURE_2D, currentTextureIndex);
			glDrawElements(GL_TRIANGLES, 12u/*ne indeksit*koko jotka piirret‰‰n t‰ll‰ kuvalla*/, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0/*indeksien piirron aloituskohta*/));
		}
	}
}
void SpriteBatch::CreateBuffer()
{
	//asetetaan buffereihin oikea piirtoj‰rjestys.
	indexPointers.clear();
	vertexPointers.clear();
	//for (std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	//{
	//	if (it->sprite != NULL)
	//	{
	//		for (int i = 0; i < it->sprite->getIndexSize(); i++)
	//		{
	//			indexPointers.push_back(&it->sprite->getIndexPointer()[i]);
	//		}
	//		for (int i = 0; i < it->sprite->getVertexSize(); i++)
	//		{
	//			vertexPointers.push_back(&it->sprite->getVertexPointer()[i]);
	//		}
	//	}
	//}
	for (int i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite != NULL)
		{
			for (int j = 0; j < drawables[i].sprite->getIndexSize(); j++)
			{
				indexPointers.push_back(&drawables[i].sprite->getIndexPointer()[j]);
			}
			for (int j = 0; j < drawables[i].sprite->getVertexSize(); j++)
			{
				vertexPointers.push_back(&drawables[i].sprite->getVertexPointer()[j]);
			}
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexPointers.size()*sizeof(GLfloat), &vertexPointers.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPointers.size()*sizeof(GLuint), &indexPointers.front(), GL_STATIC_DRAW);

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