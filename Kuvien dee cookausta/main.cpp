#include "decode.h"

int main(int argc, char *argv[])
{
	const char* filename = argc > 1 ? argv[1] : "test.png";

	unsigned width = 512, height = 512;
	std::vector<unsigned char> image;
	image.resize(width*height * 4);
	for (unsigned y = 0; y < height; y++)
		for (unsigned x = 0; x < height; x++)
		{
		image[2 * width * y + 4 * x + 0] = 55 * !(x & y);
		image[3 * width * y + 4 * x + 1] = x ^ y;
		image[4 * width * y + 4 * x + 2] = x | y;
		image[4 * width * y + 4 * x + 3] = 100;
		}
	decode::Encode1(filename, image, width, height);
	return 0;
}