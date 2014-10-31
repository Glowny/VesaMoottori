#include "ResourceManager.h"
#include <fstream>
#include <functional>
#include <iostream>
#include "lodepng.h"

bool ResourceManager::LoadPicture(std::string fileName)
{
	unsigned int hashedImageName = MyHasher(fileName); // Hasheri checkkiä varten.

	if(decodedImages.end() != decodedImages.find(hashedImageName))	// Tarkastetaan onko kuvaa vielä lisätty.
	{
		std::cout << fileName << " already in map." << std::endl;
		return false;
	}
	else
	{
		std::vector<unsigned char> decodedImage;
		unsigned width, height;
		unsigned error = lodepng::decode(decodedImage, width, height, fileName); // Pituus ja leveys ei oleellisia.

		Image image = {decodedImage, width, height};

		if(error != 0)
		{
			std::cout << "loadImage: " << error << " = " << lodepng_error_text(error) << std::endl;
			return false;
		}

		decodedImages.insert(std::pair<unsigned int, Image>(hashedImageName, image));	// Lisätään kuva mappiin.
		return true;

		//ImageInfo imageI(image, width, height);
		//if (error)
		//{
		//	//tulosta errorsoopaan "decoder error" error lodepng_error_text(error)
		//}
	}
}

Image* ResourceManager::FindImage(std::string fileName)
{
	unsigned int hashedImageName = MyHasher(fileName);

	std::map<unsigned int, Image>::iterator it = decodedImages.find(hashedImageName);
	if (decodedImages.end() != it)
		return &it->second;
	else
	{
		std::cout << "Ei löydetty kuvaa: " << fileName << std::endl;
		return NULL;
	}
}

void ResourceManager::CreateTexture(Image *image)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture class sisältää kuvan tiedot.
	//this->width = width;
	//this->height = height;
	//this->image = image;

	// Ei ole hyvin kustomoitu tämä texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		image->width,
		image->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		image->decodedImage.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
}

char* ResourceManager::ShaderReader(std::string fileName)
{
	// Avataan luettava tiedosto ja tarkistetaan onnistuminen.
	std::ifstream readFile(fileName, std::ios::in);

	/* if (readFile.is_open())
	std::cout << "Opening file: " << fileName << std::endl;
	else
	{
	std::cout << "Could not open file: " << fileName << std::endl;
	return NULL;
	} Kommentoidaan check-spammia vähän pois. */

	if (!readFile.is_open())
		return NULL;

	// Luettavan tiedoston pituus.
	readFile.seekg(0, readFile.end); // Pistetään char position filun loppuun.
	int fileLength = (int)readFile.tellg(); // Pistetään pituus ylös.
	readFile.seekg(0, readFile.beg); // Positio takasin alkuun.

	/* if (fileLength == 0)
	{
	std::cout << "ERROR: Luettavan tiedoston pituus 0." << std::endl;
	return NULL;
	}
	else
	std::cout << "Luettavan tiedoston pituus: " << fileLength << std::endl; */

	if (fileLength == 0)
		return NULL;

	std::string fileContents((std::istreambuf_iterator<char>(readFile)),
		std::istreambuf_iterator<char>()); // Kopioidaan tiedoston sisältö stringiin.
	char *tempChar = new char[fileContents.length() + 1];
	std::strcpy(tempChar, fileContents.c_str()); // Kopioidaan tiedoston sisällöt dynaamisesti luotuun char-merkkijonoon.

	//std::cout << "Closing file: " << fileName << std::endl;

	readFile.close();
	return tempChar;
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

// pistetäänkö myös mappiin?
char *ResourceManager::LoadShader(std::string filename)
{
	unsigned int hashedShaderName = MyHasher(filename);		// haetaan hashattu shaderin nimi
	if(shaders.end() != shaders.find(hashedShaderName))	// tarkastetaan onko shaderiä jo upittu // VÄÄRINPÄIN SAATANA
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
		return tempChar;	// poistetaan käytöstä jos tuntuu tyhmältä ladata joka kerta tiedostosta kun haeteaan shaderi.
	}
}

void ResourceManager::AddImageLocation(std::string filename)
{
	imageLocations.push_back(filename);
} */