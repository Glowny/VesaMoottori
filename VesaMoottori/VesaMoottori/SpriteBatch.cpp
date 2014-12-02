#include "SpriteBatch.h"
#include <algorithm>
#include <assert.h>

SpriteBatch::SpriteBatch()
{
	//changes = true;
	//glGenBuffers(2, &buffer[0]);
	size = vector2f(0.0f, 0.0f);
	CreateBuffers();
}

SpriteBatch::SpriteBatch(GraphicsDevice &window)
{
	//changes = true;
	//glGenBuffers(2, &buffer[0]);
	size = vector2f((float) window.GetSize().x, (float) window.GetSize().y);
	(this->graphicsDevice) = &window;
	CreateBuffers();
}

void SpriteBatch::Draw()
{
	// K‰ytet‰‰n pixel-koordinaatistoa.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, size.x, size.y, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	//GLenum error = glGetError();
	//assert(error == GL_INVALID_VALUE);
	//assert(error == GL_INVALID_OPERATION);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Valitaan k‰ytett‰v‰t shaderit.
	if(shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// K‰ynnistet‰‰n default shaderi.
	}

	vertexData.clear(); // Clearataan vanhat shitit.
	indexData.clear();
	int spriteCount = 0; // Kuinka monta sprite‰ piirrett‰‰n.

	if(drawables.size() != 0) // Onko piirrett‰vi‰.
	{
<<<<<<< HEAD
		for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
		{
<<<<<<< HEAD
<<<<<<< HEAD
			// Tarkastetaan ett‰ spritell‰ on koko ja texture.
			if ((it->sprite->GetSizeSet()) && (it->sprite->GetTextureSet()))
			{
				for (int i = 0; i < it->sprite->GetIndexSize(); i++)
					indexData.push_back(it->sprite->GetIndexData()[i] + spriteCount * 4); // Yhden neliˆn piirt‰miseen tarvittava indeksim‰‰r‰, t‰ytyy vaihtaa jos halutaan erimuotoisia kuvioita.
				for (int i = 0; i < it->sprite->GetVertexSize(); i++)
					vertexData.push_back(it->sprite->GetVertexData()[i]);
				spriteCount++;
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), &vertexData[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), &indexData[0], GL_STATIC_DRAW);

		const GLint posLocation = shaderProgram->GetAttributeLocation("attrPosition");
		const GLint colorLocation = shaderProgram->GetAttributeLocation("attrColor");
		const GLint texLocation = shaderProgram->GetAttributeLocation("textPosition");

		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(colorLocation);
		glEnableVertexAttribArray(texLocation);

		glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vertexData[0]);
		glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vertexData[2]);
		glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vertexData[5]);

		glDrawElements(GL_TRIANGLES, indexData.size() , GL_UNSIGNED_INT, &indexData[0]);

		//// Piirrett‰‰n vain spritej‰ - pit‰‰ luoda uudestaan muille tyypeille jos tehd‰‰n.
		//if((it->sprite->GetSizeSet()) && (it->sprite->GetTextureSet()))
		//{
		//	it->sprite->Draw(arrayBuffer, elementArrayBuffer);
		//	glBufferData(GL_ARRAY_BUFFER, 28 * sizeof(GLfloat), &(it->sprite->VERTEX_DATA), GL_STATIC_DRAW);
		//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &(it->sprite->INDEX_DATA), GL_STATIC_DRAW);
		//	glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(it->sprite->INDEX_DATA));
		//}
=======
=======
>>>>>>> parent of f6e486e... Ei toimi viel√§
			if((it->sprite->GetSizeSet()) && (it->sprite->GetTextureSet()))
			{

			}
		}

		// Piirrett‰‰n vain spriteh‰ - pit‰‰ luoda uudestaan muille tyypeille jos tehd‰‰n.
=======
>>>>>>> parent of e336557... Backup II
		glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertexPointers.size()*sizeof(GLfloat), vertexPointers.front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPointers.size()*sizeof(GLuint), &indexPointers.front(), GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((drawables.size() - 1) * 6u * sizeof(GLuint)));

		// Siivotaan j‰lki‰.
		glBindTexture(GL_TEXTURE_2D, 0u);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);
		glUseProgram(0);
>>>>>>> parent of f6e486e... Ei toimi viel√§
	}

	// Siivotaan j‰lki‰.
	glBindTexture(GL_TEXTURE_2D, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glUseProgram(0);
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

void SpriteBatch::CreateBuffers()
{
	glGenBuffers(1, &arrayBuffer);
	glGenBuffers(1, &elementArrayBuffer);
}

SpriteBatch::~SpriteBatch()
{
}

/*
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

void SpriteBatch::CreateBuffer()
{
	indexPointers.clear();
	vertexPointers.clear();

	for(unsigned i = 0; i < drawables.size(); i++)
	{
		if(drawables[i].sprite != NULL)
		{
			for(int j = 0; j < drawables[i].sprite->getIndexSize(); j++)
			{
				indexPointers.push_back(drawables[i].sprite->getIndexPointer()[j] + i * 4); // yhden neliˆn piirt‰miseen tarvittava indeksim‰‰r‰, t‰ytyy vaihtaa jos halutaan erimuotoisia kuvioita
			}
			for(int j = 0; j < drawables[i].sprite->getVertexSize(); j++)
			{
				vertexPointers.push_back(&drawables[i].sprite->getVertexPointer()[j]);
			}
		}
	}
}

asetetaan buffereihin oikea piirtoj‰rjestys.
for (std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
{
	if (it->sprite != NULL)
	{
		for (int i = 0; i < it->sprite->getIndexSize(); i++)
		{
			indexPointers.push_back(&it->sprite->getIndexPointer()[i]);
		}
		for (int i = 0; i < it->sprite->getVertexSize(); i++)
		{
			vertexPointers.push_back(&it->sprite->getVertexPointer()[i]);
		}
	}
}

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, 640, 480, 0, 1, -1);
glMatrixMode(GL_MODELVIEW);
*/