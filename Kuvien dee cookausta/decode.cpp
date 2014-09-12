#include "decode.h"


decode::decode()
{
}


decode::~decode()
{
}

std::vector<unsigned char> decode::Decode1(const char* filename)
{
	std::vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filename);
	if (error) std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
	return image;
}
std::vector<unsigned char> decode::Decode2(const char* filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	unsigned width, height;

	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(image, width, height, png);

	if (error) std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
	return image;
}

std::vector<unsigned char> decode::Decode3State(const char* filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	unsigned width, height;
	lodepng::State state; // t‰st‰ saa irti vaikka ja mit‰, vois pist‰‰ maholliseksi hakea
	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(image, width, height, state, png);

	if (error) std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
	return image;

}

void decode::Encode1(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	unsigned error = lodepng::encode(filename, image, width, height);

	if (error) std::cout << "encoder error" << error << ": " << lodepng_error_text(error) << std::endl;
}

void decode::Encode2(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(png, image, width, height);
	if (!error) lodepng::save_file(png, filename);

	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}
void decode::Encode3(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	std::vector<unsigned char> png;
	lodepng::State state;

	unsigned error = lodepng::encode(png, image, width, height, state);
	if (!error) lodepng::save_file(png, filename);
	if (error) std::cout << "encoder error" << error << ": " << lodepng_error_text(error) << std::endl;
}