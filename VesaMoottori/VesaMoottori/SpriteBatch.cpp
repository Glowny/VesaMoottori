
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

void SpriteBatch::CreateBuffer()
{

	indexData.clear();
	vertexData.clear();

	for (unsigned i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite != NULL)
		{
			for (int j = 0; j < drawables[i].sprite->getIndexSize(); j++)
			{
				indexData.push_back(drawables[i].sprite->getIndexPointer()[j] + i * 4); // yhden neliön piirtämiseen tarvittava indeksimäärä, täytyy vaihtaa jos halutaan erimuotoisia kuvioita
			}
			for (int j = 0; j < drawables[i].sprite->getVertexSize(); j++)
			{

				vertexData.push_back(drawables[i].sprite->getVertexPointer()[j]);
			}
		}
	}

}

void SpriteBatch::Update()
{
	if (changes)
	{
		Sort(); // Sortataan ennen buffereiden tekoa.
		CreateBuffer();
		changes = false;

		glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GLfloat), &vertexData.front(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLuint), &indexData.front(), GL_DYNAMIC_DRAW);
	}
	CreateBuffer();
	for (unsigned i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite->positionChanged)
			drawables[i].sprite->changePositionData(size);

		if (drawables[i].sprite->texturePositionChanged)
			drawables[i].sprite->changeTexturePosition();

		if (drawables[i].sprite->colorChanged)
			drawables[i].sprite->changeColorData();
	}

	// glBufferSubData
	// GL_DYNAMIC_DRAW

	glBufferSubData(GL_ARRAY_BUFFER, 0u, vertexData.size()*sizeof(GLfloat), &vertexData.front());



}
void SpriteBatch::Draw()
{

	if (shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// Käynnistetään default shaderi.
	}

	// Tarkistetaan onko mitään piirettävää edes.
	// Ohjelma kaatuu jos ei ole asetettu tekstuuria jokaiselle piirettävälle,
	// Tähän tehtävä jonkinlainen korjaus

	if (drawables.size() != 0) 
	{
		GLuint currentTextureIndex = drawables[0].sprite->texture->getTextureIndex();
		unsigned textureAmount = 0;
		for (unsigned i = 0; i < drawables.size(); i++)
		{
			// tarkastetaan onko tämän indeksin tekstuuri sama kuin edellisen, [0]-indeksi aina true.
			if (drawables[i].sprite->texture->getTextureIndex() == currentTextureIndex)		
			{
				textureAmount++;
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, currentTextureIndex);

				// Kun tulee indeksi jonka tekstuuri on eri kuin edellisellä kierroksella,
				// piiretään kaikki edelliset joilla oli sama tekstuuri.
				// Aloituskohta on indeksivektorin indeksien määrä (6) kerrottuna edellisen kierroksen kierrosmäärällä (i-1). 

				// 6u toimii vain jos kaikkien spritejen indeksimäärä on sama (6),
				// jos halutaan piirtää indeksimäärältään erikokoisia, on otettava talteen jo piirrettyjen indeksien koko, 
				// sekä selvittää ehtolauseessa, onko indeksimäärä sama kuin edellisessä.
				// Eli vastaava muuttuja currentTextureIndex:lle.
				// Kannattaa varmaan toteuttaa 6u:n tilalle sprite->getIndexSize(), VASTA kun aletaan tukemaan erilaisia indeksimääriä,
				// näin pysyy ajatus paremmin tehdessä.


				glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((i - textureAmount) * 6u * sizeof(GLuint)));

				// lopuksi tämän indeksin piirrettävä tekstuuri, ja asetetaan määrä ykköseen.
				currentTextureIndex = drawables[i].sprite->texture->getTextureIndex();
				textureAmount = 1;		// ehkä 1
				glBindTexture(GL_TEXTURE_2D, 0u);
			}
		};
		// for-loopin jälkeen piiretään kaikki ne spritet, joilla on sama tekstuuri kuin viimeisen indeksin tekstuurilla.



		currentTextureIndex = drawables[drawables.size()-1].sprite->texture->getTextureIndex();
		glBindTexture(GL_TEXTURE_2D, currentTextureIndex);
		glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((drawables.size() - textureAmount) * 6u * sizeof(GLuint)));
		glBindTexture(GL_TEXTURE_2D, 0u);


		//Debugaukseen, saa poistaa.
		vertexData;
		indexData;
		//
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
		// Sortataan piirrettävät orderin mukaan.
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

//asetetaan buffereihin oikea piirtojärjestys.
//for (std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
//{
//	if (it->sprite != NULL)
//	{
//		for (int i = 0; i < it->sprite->getIndexSize(); i++)
//		{
//			indexData.push_back(&it->sprite->getIndexPointer()[i]);
//		}
//		for (int i = 0; i < it->sprite->getVertexSize(); i++)
//		{
//			vertexData.push_back(&it->sprite->getVertexPointer()[i]);
//		}
//	}
//}