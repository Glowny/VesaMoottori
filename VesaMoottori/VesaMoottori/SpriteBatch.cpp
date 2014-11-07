#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
	changes = true;
	maxOrder = 0;
}

void SpriteBatch::Draw()
{



}

void SpriteBatch::Sort()
{
	for(std::vector<Drawable>::iterator it = drawables.begin(); it != drawables.end(); it++)
	{
		
	}
}

void SpriteBatch::SetMaxOrder()
{

}

void SpriteBatch::CheckMaxOrder(int order)
{
	if(order > maxOrder)
		maxOrder = order;
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
	drawables.push_back(temp);
	CheckMaxOrder(order);
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
	drawables.push_back(temp);
	CheckMaxOrder(order);
}

void SpriteBatch::AddShaderProgram(ShaderProgram &shaderProgram)
{
	(this->shaderProgram) = &shaderProgram;
}

void SpriteBatch::SetDevice(GraphicsDevice &graphicsDevice)
{
	(this->graphicsDevice) = &graphicsDevice;
}