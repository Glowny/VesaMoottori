#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() : changes(true)
{
	size = vector2f(0.0f, 0.0f);
	//glGenBuffers(2, &buffer[0]);
}

SpriteBatch::SpriteBatch(GraphicsDevice &window) : changes(true)
{
	size = vector2f((float)window.GetSize().x, (float)window.GetSize().y);
	(this->graphicsDevice) = &window;
	glGenBuffers(2, &buffer[0]);
}

void SpriteBatch::Draw()
{
	Update();

	if (shaderProgram->GetLinkStatus()) // Tarkistetaan shaderin linkkaus.
		shaderProgram->RunProgram();
	else
	{
		// K‰ynnistet‰‰n default shaderi.
	}

	// Tarkistetaan onko mit‰‰n piirett‰v‰‰ edes.
	// TO-FIX: Ohjelma kaatuu jos ei ole asetettu tekstuuria jokaiselle piirett‰v‰lle.

	if (drawables.size() != 0) 
	{
		GLuint currentTextureIndex = drawables[0].sprite->texture->GetIndex();
		unsigned textureAmount = 0;
		for (unsigned i = 0; i < drawables.size(); i++)
		{
			// Tarkastetaan onko t‰m‰n indeksin tekstuuri sama kuin edellisen, [0]-indeksi aina true.
			if (drawables[i].sprite->texture->GetIndex() == currentTextureIndex)		
				textureAmount++;
			else
			{
				glBindTexture(GL_TEXTURE_2D, currentTextureIndex);

				/* Kun tulee indeksi jonka tekstuuri on eri kuin edellisell‰ kierroksella,
				 piiret‰‰n kaikki edelliset joilla oli sama tekstuuri.
				 Aloituskohta on indeksivektorin indeksien m‰‰r‰ (6) kerrottuna edellisen kierroksen kierrosm‰‰r‰ll‰ (i-1). 

				 6u toimii vain jos kaikkien spritejen indeksim‰‰r‰ on sama (6),
				 jos halutaan piirt‰‰ indeksim‰‰r‰lt‰‰n erikokoisia, on otettava talteen jo piirrettyjen indeksien koko, 
				 sek‰ selvitt‰‰ ehtolauseessa, onko indeksim‰‰r‰ sama kuin edellisess‰.
				 Eli vastaava muuttuja currentTextureIndex:lle.
				 Kannattaa varmaan toteuttaa 6u:n tilalle sprite->getIndexSize(), VASTA kun aletaan tukemaan erilaisia indeksim‰‰ri‰,
				 n‰in pysyy ajatus paremmin tehdess‰. */

				glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((i - textureAmount) * 6u * sizeof(GLuint)));

				// Lopuksi t‰m‰n indeksin piirrett‰v‰ tekstuuri, ja asetetaan m‰‰r‰ ykkˆseen.
				currentTextureIndex = drawables[i].sprite->texture->GetIndex();
				textureAmount = 1;		// ehk‰ 1
				glBindTexture(GL_TEXTURE_2D, 0u);
			}
		}
		// For-loopin j‰lkeen piiret‰‰n kaikki ne spritet, joilla on sama tekstuuri kuin viimeisen indeksin tekstuurilla.

		currentTextureIndex = drawables[drawables.size()-1].sprite->texture->GetIndex();
		glBindTexture(GL_TEXTURE_2D, currentTextureIndex);
		glDrawElements(GL_TRIANGLES, textureAmount * 6u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>((drawables.size() - textureAmount) * 6u * sizeof(GLuint)));
		glBindTexture(GL_TEXTURE_2D, 0u);
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
void SpriteBatch::ClearDrawables()
{
	drawables.clear();	// Saattaa joutua korjaamaan.
}

void SpriteBatch::SetShaderProgram(ShaderProgram &shaderProgram)
{
	(this->shaderProgram) = &shaderProgram;
}

void SpriteBatch::SetDevice(GraphicsDevice &graphicsDevice)
{
	(this->graphicsDevice) = &graphicsDevice;
}

void SpriteBatch::Update()
{
	if(changes)
	{
		// T‰ll‰ hetkell‰ Spritejen j‰rjestyst‰ ei voi vaihtaa SpriteaBatchiin lis‰‰miseen j‰lkeen.
		//Sort(); // Sortataan ennen buffereiden tekoa.
		CreateBuffer();
		changes = false;

		glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GLfloat), &vertexData.front(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLuint), &indexData.front(), GL_DYNAMIC_DRAW);
	}

	CreateBuffer();

	for(unsigned i = 0; i < drawables.size(); i++)
	{
		if(drawables[i].sprite->positionChanged)
			drawables[i].sprite->changePositionData();

		if(drawables[i].sprite->texturePositionChanged)
			drawables[i].sprite->changeTexturePositionData();

		if(drawables[i].sprite->colorChanged)
			drawables[i].sprite->changeColorData();
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0u, vertexData.size()*sizeof(GLfloat), &vertexData.front());
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

vector2f SpriteBatch::TextureToGLCoord(float x, float y, vector2f spriteSize)
{
	vector2f temp;
	temp.x = (x / spriteSize.x);
	temp.y = (y / spriteSize.y);
	return temp;
}

vector2f SpriteBatch::PositionToGlCoord(float x, float y)
{
	vector2f temp;
	temp.x = 2*(x / size.x) -1;
	temp.y = 2*(y / size.y) -1;
	return temp;
}

GLfloat SpriteBatch::ColorToGLCoord(GLfloat color)
{
	return color / 255;
}

void SpriteBatch::CreateBuffer()
{
	indexData.clear();
	vertexData.clear();

	for(unsigned i = 0; i < drawables.size(); i++)
	{
		if(drawables[i].sprite != NULL)
		{
			for(int j = 0; j < drawables[i].sprite->getIndexSize(); j++)
			{
				GLuint index = drawables[i].sprite->getIndexPointer()[j] + i * 4;
				indexData.push_back(index); // Yhden neliˆn piirt‰miseen tarvittava indeksim‰‰r‰, t‰ytyy vaihtaa jos halutaan erimuotoisia kuvioita.
			}

			GLfloat vertexArray[7];
			int index = 0;

			for(int j = 0; j < drawables[i].sprite->getVertexSize(); j++)
			{
				vertexArray[index] = drawables[i].sprite->getVertexPointer()[j];
				index++;
				if(index > 6)
				{
					vector2f positionGL = PositionToGlCoord(vertexArray[0], vertexArray[1]);
					vector2f textureGL = TextureToGLCoord(vertexArray[5], vertexArray[6], drawables[i].sprite->getTextureSize());
					GLfloat red = ColorToGLCoord(vertexArray[2]);
					GLfloat green = ColorToGLCoord(vertexArray[3]);
					GLfloat blue = ColorToGLCoord(vertexArray[4]);

					vertexArray[0] = positionGL.x * -1;	// K‰‰nnetty.
					vertexArray[1] = positionGL.y * -1;
					vertexArray[2] = red;
					vertexArray[3] = blue;
					vertexArray[4] = green;
					vertexArray[5] = textureGL.x;
					vertexArray[6] = textureGL.y;

					for(int i = 0; i < 7; i++)
						vertexData.push_back(vertexArray[i]);

					index = 0;
				}
			}
		}
	}
}

void SpriteBatch::UnbindBuffers()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
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
	UnbindBuffers();
}