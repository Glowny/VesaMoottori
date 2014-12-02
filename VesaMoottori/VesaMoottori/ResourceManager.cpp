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
		return true;
	}
	else
	{
		std::vector<unsigned char> decodedImage;
		unsigned width, height;
		unsigned error = lodepng::decode(decodedImage, width, height, fileName); // Pituus ja leveys ei oleellisia.

		Image image = { decodedImage, width, height };

		if(error != 0)
		{
			std::cout << "LoadPicture: " << error << " = " << lodepng_error_text(error) << std::endl;
			return false;
		}

		decodedImages.insert(std::pair<unsigned int, Image>(hashedImageName, image));	// Lisätään kuva mappiin.
		return true;
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

Texture* ResourceManager::CreateTexture(std::string fileName, std::string textureName, vector2f position, float scale)
{
	Texture *tempTexture;

	if(LoadPicture(fileName)) // Jos kuvan lataaminen onnistuu.
		tempTexture = new Texture(FindImage(fileName), position, scale); // Luodaan tekstuuri kuvan perusteella.
	else
		return NULL;

	textures.insert(std::pair<std::string, Texture*>(textureName, tempTexture)); // Lisätään texture-mappiin.
	return tempTexture; // Palautetaan suoraan pointteri luotuun tekstuuriin.
}

char* ResourceManager::LoadShader(std::string fileName, std::string shaderName)
{
	char *code = ShaderReader(fileName);
	shaders.insert(std::pair<std::string, char*>(shaderName, code));
	return code;
}

char* ResourceManager::FindShader(std::string shaderName)
{
	return shaders[shaderName];
}

unsigned int ResourceManager::MyHasher(std::string filename)
{
	std::hash<std::string> Hasher;
	unsigned int hash = Hasher(filename);
	return hash;
}

char* ResourceManager::ShaderReader(std::string fileName)
{
	// Avataan luettava tiedosto ja tarkistetaan onnistuminen.
	std::ifstream readFile(fileName, std::ios::in);

	if (!readFile.is_open())
	{
		std::cout << "ERROR: Could not open file: " << fileName << std::endl;
		return NULL;
	}

	// Luettavan tiedoston pituus.
	readFile.seekg(0, readFile.end); // Pistetään char position filun loppuun.
	int fileLength = (int)readFile.tellg(); // Pistetään pituus ylös.
	readFile.seekg(0, readFile.beg); // Positio takasin alkuun.

	if (fileLength == 0)
	{
		std::cout << "ERROR: Luettavan tiedoston pituus 0." << std::endl;
		return NULL;
	}

	std::string fileContents((std::istreambuf_iterator<char>(readFile)),
							 std::istreambuf_iterator<char>()); // Kopioidaan tiedoston sisältö stringiin.
	char *tempChar = new char[fileContents.length() + 1];
	std::strcpy(tempChar, fileContents.c_str()); // Kopioidaan tiedoston sisällöt dynaamisesti luotuun char-merkkijonoon.

	readFile.close();
	return tempChar;
}


//Texture* ResourceManager::CreateTexture(std::string pictureName, std::string textureName)
//{
//	Texture tempTexture = Texture(FindImage(pictureName), vector2f(0,0), 1); // Luodaan tekstuuri kuvan perusteella.
//	textures.insert(std::pair<std::string, Texture>(textureName, tempTexture)); // Lisätään texture-mappiin.
//	return &textures[textureName]; // Palautetaan suoraan pointteri luotuun tekstuuriin.
//}

//Texture* ResourceManager::FindTexture(std::string textureName)
//{
//	return &textures[textureName];
//}

/*char* ResourceManager::FindShader(std::string filename)
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