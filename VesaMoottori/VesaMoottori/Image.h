#pragma once
#include <vector>
struct Image
{
	int width;
	int height;
	std::vector<unsigned char> decodedImage;

	Image(std::vector<unsigned char> DecodedImage, unsigned Width, unsigned Height)
	{
		decodedImage = DecodedImage;
		width = Width;
		height = Height;
	}

	Image()
	{
		//width = 0;
		//height = 0;
	}
};