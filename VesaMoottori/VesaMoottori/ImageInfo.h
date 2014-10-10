#include <vector>
#include <iostream>
#pragma once
typedef std::vector<unsigned char> DecodedImage;
struct ImageInfo
{
	ImageInfo(DecodedImage DecodedImage, unsigned Width, unsigned Height)
	{
		decodedImage = DecodedImage;
		width = Width;
		height = Height;
	}
	DecodedImage decodedImage;
	unsigned width;
	unsigned height;

};