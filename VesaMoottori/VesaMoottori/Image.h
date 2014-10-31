#pragma once
#include <vector>
//typedef std::vector<unsigned char> Image;

struct Image
{
	int width;
	int height;
	std::vector<unsigned char> decodedImage;

	Image(){};
	Image(std::vector<unsigned char> DecodedImage, unsigned Width, unsigned Height)
	{
		decodedImage = DecodedImage;
		width = Width;
		height = Height;
	}
};