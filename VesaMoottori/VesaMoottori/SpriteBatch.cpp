
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

	indexPointers.clear();
	vertexPointers.clear();

	for (unsigned i = 0; i < drawables.size(); i++)
	{
		if (drawables[i].sprite != NULL)
		{
			for (int j = 0; j < drawables[i].sprite->getIndexSize(); j++)
			{
				indexPointers.push_back(drawables[i].sprite->getIndexPointer()[j] + i * 4); // yhden neliˆn piirt‰miseen tarvittava indeksim‰‰r‰, t‰ytyy vaihtaa jos halutaan erimuotoisia kuvioita
			}
			for (int j = 0; j < drawables[i].sprite->getVertexSize(); j++)
			{
				vertexPointers.push_back(&drawables[i].sprite->getVertexPointer()[j]);
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPointers.size()*sizeof(GLuint), &indexPointers.front(), GL_STATIC_DRAW);



}
void SpriteBatch::Draw()
{

	if (shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// K‰ynnistet‰‰n default shaderi.
	}

	// Tarkistetaan onko mit‰‰n piirett‰v‰‰ edes.
	// Ohjelma kaatuu jos ei ole asetettu tekstuuria jokaiselle piirett‰v‰lle,
	// T‰h‰n teht‰v‰ jonkinlainen korjaus

	if (drawables.size() != 0) 
	{
		GLuint currentTextureIndex = drawables[0].sprite->texture->getTextureIndex();
		unsigned textureAmount = 0;
		for (unsigned i = 0; i < drawables.size(); i++)
		{
			// tarkastetaan onko t‰m‰n indeksin tekstuuri sama kuin edellisen, [0]-indeksi aina true.
			if (drawables[i].sprite->texture->getTextureIndex() == currentTextureIndex)		
			{
				textureAmount++;
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, currentTextureIndex);

				// Kun tulee indeksi jonka tekstuuri on eri kuin edellisell‰ kierroksella,
				// piiret‰‰n kaikki edelliset joilla oli sama tekstuuri.
				// Aloituskohta on indeksivektorin indeksien m‰‰r‰ (6) kerrottuna edellisen kierroksen kierrosm‰‰r‰ll‰ (i-1). 

				// 6u toimii vain jos kaikkien spritejen indeksim‰‰r‰ on sama (6),
				// jos halutaan piirt‰‰ indeksim‰‰r‰lt‰‰n erikokoisia, on otettava talteen jo piirrettyjen indeksien koko, 
				// sek‰ selvitt‰‰ ehtolauseessa, onko indeksim‰‰r‰ sama kuin edellisess‰.
				// Eli vastaava muuttuja currentTextureIndex:lle.
				// Kannattaa varmaan toteuttaa 6u:n tilalle sprite->getIndexSize(), VASTA kun aletaan tukemaan erilaisia indeksim‰‰ri‰,
				// n‰in pysyy ajatus paremmin tehdess‰.

				glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((i - 1) * 6u * sizeof(GLuint)));

				// lopuksi t‰m‰n indeksin piirrett‰v‰ tekstuuri, ja asetetaan m‰‰r‰ ykkˆseen.
				currentTextureIndex = drawables[i].sprite->texture->getTextureIndex();
				textureAmount = 1;
				glBindTexture(GL_TEXTURE_2D, 0u);
			}
		};
		// for-loopin j‰lkeen piiret‰‰n kaikki ne spritet, joilla oli sama tekstuuri kuin viimeisen indeksin tekstuurilla.
		glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((drawables.size() - 1) * 6u * sizeof(GLuint)));

		glBindTexture(GL_TEXTURE_2D, 0u);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);
		glUseProgram(0);

		// T‰m‰ koodi ei jostain syyst‰ piirr‰ useampaa kuin yht‰ sprite‰, mutta virhe on muualla kuin tekstuurintarkistuksessa.
		// Ei toiminut ennen kuin lis‰sin uudet jutut.

		//Debugaukseen, saa poistaa.
		vertexPointers;
		indexPointers;
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

//asetetaan buffereihin oikea piirtoj‰rjestys.
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