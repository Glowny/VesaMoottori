#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}
void ResourceManager::addImage(std::string filename, DecodedImage img)
{
	unsigned int hashedImageName = myHasher(filename);
	if (decodedImages.end() != decodedImages.find(hashedImageName))	// tarkastetaan onko kuvaa viel‰ lis‰tty
	{
		decodedImages.insert(std::pair<unsigned int, DecodedImage>(hashedImageName, img));	// lis‰t‰‰n kuva
	}
}

DecodedImage* ResourceManager::findImage(std::string filename)
{
	unsigned int hashedImageName = myHasher(filename);

	std::map<unsigned int, DecodedImage>::iterator it = decodedImages.find(hashedImageName);
	if (decodedImages.end() != it)
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}
}

void ResourceManager::addImageLocation(std::string filename)
{
	imageLocations.push_back(filename);
}
unsigned int ResourceManager::myHasher(std::string filename)
{
	std::hash<std::string> Hasher;
	unsigned int hash = Hasher(filename);
	return hash;
}

ResourceManager::~ResourceManager()
{

}
