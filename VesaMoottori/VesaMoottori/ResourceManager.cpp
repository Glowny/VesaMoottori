#include "ResourceManager.h"
#include <iostream>

void ResourceManager::LoadImage(std::string filename)
{
	unsigned int hashedImageName = MyHasher(filename);
	if (decodedImages.end() != decodedImages.find(hashedImageName))	// tarkastetaan onko kuvaa vielä lisätty
	{
		// error lisätty jo
	}
	else
	{
		DecodedImage image;
		unsigned width, height;
		unsigned error = lodepng::decode(image, width, height, filename);
		std::cout << "loadImage: " << error << " : " << lodepng_error_text(error) << std::endl;
		if (error)
		{
			//tulosta errorsoopaan "decoder error" error lodepng_error_text(error)
		}
		decodedImages.insert(std::pair<unsigned int, DecodedImage>(hashedImageName, image));	// lisätään kuva mappiin
	}
}

DecodedImage* ResourceManager::FindImage(std::string filename)
{
	unsigned int hashedImageName = MyHasher(filename);

	std::map<unsigned int, DecodedImage>::iterator it = decodedImages.find(hashedImageName);
	if (decodedImages.end() != it)
	{
		return &it->second;
	}
	else
	{
		return NULL;	// varmaan errormessagea
	}
}
char* ResourceManager::FindShader(std::string filename)
{
	unsigned int  hashedShaderName = MyHasher(filename);
	std::map < unsigned int, char* >::iterator it = shaders.find(hashedShaderName);
	if (shaders.end() != it)
	{
		return it->second;		// !!!!!!!!!
	}
	else
	{
		return NULL;	//varmaan errormessagea
	}
}
// pistetäänkö myös mappiin?
char *ResourceManager::LoadShader(std::string filename)
{
	unsigned int hashedShaderName = MyHasher(filename);		// haetaan hashattu shaderin nimi
	if (shaders.end() != shaders.find(hashedShaderName))	// tarkastetaan onko shaderiä jo upittu // VÄÄRINPÄIN SAATANA
	{
		// error ei olee shaderia
		return NULL;
	}
	else
	{
		std::ifstream readFile(filename, std::ios::in);
		if (readFile.is_open())
		{
		}
		else
		{
			//errormessage, could not open file
			return NULL;
		}
		readFile.seekg(0, readFile.end);
		int fileLength = (int) readFile.tellg();
		readFile.seekg(0, readFile.beg);
		if (fileLength == 0)
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
		return tempChar;	// poistetaan käytöstä jos tuntuu tyhmältä ladata joka kerta tiedostosta kun haeteaan shaderi.
	}
}

void ResourceManager::AddImageLocation(std::string filename)
{
	imageLocations.push_back(filename);
}

unsigned int ResourceManager::MyHasher(std::string filename)
{
	std::hash<std::string> Hasher;
	unsigned int hash = Hasher(filename);
	return hash;
}