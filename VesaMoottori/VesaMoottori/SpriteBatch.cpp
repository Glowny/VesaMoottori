
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
	size = vector2f((float) window.GetSize().x, (float) window.GetSize().y);
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

	for (unsigned i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite->positionChanged)
			drawables[i].sprite->changePositionData(size);

		if (drawables[i].sprite->texturePositionChanged)
			drawables[i].sprite->changeTexturePosition();

		if (drawables[i].sprite->colorChanged)
			drawables[i].sprite->changeColorData();
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexPointers.size()*sizeof(GLfloat), vertexPointers.front(), GL_STATIC_DRAW);


}
void SpriteBatch::Draw()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPointers.size()*sizeof(GLuint), &indexPointers.front(), GL_STATIC_DRAW);

	if (shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// K‰ynnistet‰‰n default shaderi.
	}
	GLuint currentTextureIndex = 1;
	//for (unsigned i = 0; i < drawables.size(); i++)
	{
		/*if (drawables[i].sprite->texture->getTextureIndex() != currentTextureIndex)*/
		{
			/*currentTextureIndex = drawables[i].sprite->texture->getTextureIndex();*/
			glBindTexture(GL_TEXTURE_2D, currentTextureIndex);
			glDrawElements(GL_TRIANGLES, 12u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0 * sizeof(GLuint)));
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
	for (unsigned i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite != NULL)
		{
			int currentVertexSize = vertexPointers.size();
			for (int j = 0; j < drawables[i].sprite->getIndexSize(); j++)
			{
				indexPointers.push_back(drawables[i].sprite->getIndexPointer()[j] + currentVertexSize - i * 24u);
			}
			for (int j = 0; j < drawables[i].sprite->getVertexSize(); j++)
			{
				vertexPointers.push_back(&drawables[i].sprite->getVertexPointer()[j]);
			}
		}
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

	for (std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		// Sortataan piirrett‰v‰t orderin mukaan.
		std::sort(drawables.begin(), drawables.end(),
			[](Drawable a, Drawable b){return (a.drawOrder > b.drawOrder); });
	}

}

std::vector<Drawable>::iterator SpriteBatch::FindLocation(int order)
{
	std::vector<Drawable>::iterator it;
	for (it = drawables.begin(); it != drawables.end(); it++)
	{
		if (it->drawOrder >= order)
			break;
	}
	return it;
}

SpriteBatch::~SpriteBatch()
{
	// TERMINATE EVERYTHING
}