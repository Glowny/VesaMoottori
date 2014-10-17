#include "ResourceManager.h"
#include <fstream>
#include <functional>
#include <iostream>
#include "lodepng.h"

bool ResourceManager::LoadPicture(std::string filename)
{
	unsigned int hashedImageName = MyHasher(filename); // Hasheri checkki� varten.

	if(decodedImages.end() != decodedImages.find(hashedImageName))	// Tarkastetaan onko kuvaa viel� lis�tty.
	{
		std::cout << filename << " already in map." << std::endl;
		return false;
	}
	else
	{
		DecodedImage image;
		unsigned width, height;
		unsigned error = lodepng::decode(image, width, height, filename); // Pituus ja leveys ei oleellisia.
		if(error != 0)
		{
			std::cout << "loadImage: " << error << " = " << lodepng_error_text(error) << std::endl;
			return false;
		}

		decodedImages.insert(std::pair<unsigned int, DecodedImage>(hashedImageName, image));	// Lis�t��n kuva mappiin.
		return true;

		//ImageInfo imageI(image, width, height);
		//if (error)
		//{
		//	//tulosta errorsoopaan "decoder error" error lodepng_error_text(error)
		//}
	}
}

DecodedImage* ResourceManager::FindImage(std::string filename)
{
	unsigned int hashedImageName = MyHasher(filename);

	std::map<unsigned int, DecodedImage>::iterator it = decodedImages.find(hashedImageName);
	if (decodedImages.end() != it)
		return &it->second;
	else
	{
		std::cout << "Ei l�ydetty kuvaa: " << filename << std::endl;
		return NULL;
	}
}

unsigned int ResourceManager::MyHasher(std::string filename)
{
	std::hash<std::string> Hasher;
	unsigned int hash = Hasher(filename);
	return hash;
}


/* char* ResourceManager::FindShader(std::string filename)
{
	unsigned int  hashedShaderName = MyHasher(filename);
	std::map < unsigned int, char* >::iterator it = shaders.find(hashedShaderName);
	if(shaders.end() != it)
	{
		return it->second;		// !!!!!!!!!
	}
	else
	{
		return NULL;	//varmaan errormessagea
	}
}

// pistet��nk� my�s mappiin?
char *ResourceManager::LoadShader(std::string filename)
{
	unsigned int hashedShaderName = MyHasher(filename);		// haetaan hashattu shaderin nimi
	if(shaders.end() != shaders.find(hashedShaderName))	// tarkastetaan onko shaderi� jo upittu // V��RINP�IN SAATANA
	{
		// error ei olee shaderia
		return NULL;
	}
	else
	{
		std::ifstream readFile(filename, std::ios::in);
		if(readFile.is_open())
		{
		}
		else
		{
			//errormessage, could not open file
			return NULL;
		}
		readFile.seekg(0, readFile.end);
		int fileLength = (int)readFile.tellg();
		readFile.seekg(0, readFile.beg);
		if(fileLength == 0)
		{
			//errormessage, file empty
		}
		else
		{
		}
		std::string fileContents((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
		char *tempChar = new char[fileContents.length() + 1];
		std::strcpy(tempChar, fileContents.c_str());

		readFile.close();
		shaders.insert(std::pair<unsigned int, char*>(hashedShaderName, tempChar));
		return tempChar;	// poistetaan k�yt�st� jos tuntuu tyhm�lt� ladata joka kerta tiedostosta kun haeteaan shaderi.
	}
}

void ResourceManager::AddImageLocation(std::string filename)
{
	imageLocations.push_back(filename);
} */