#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>

typedef std::vector<unsigned char> DecodedImage;	// voitais k�ytt�� projektissa enemm�n

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void addImage(std::string filename,std::vector<unsigned char> image);	//dekoodattu kuva, name toimii keyn�
	DecodedImage* findImage(std::string filename);
	void addImageLocation(std::string filename);	//kuvan sijainti vektoriin
private:
	std::map<unsigned int, DecodedImage> decodedImages; // imagelocationista kuva, joka dekoodataan ja pistet��n t�nne. T�m� ottaa my�s nimen
	std::vector<std::string> imageLocations; // ei ehk� v�ltt�m�t�n; toisaalta voidaan tarkistaa onko jo upittu. Helppo muokattavuus jos vaikka tekstifiless�
	unsigned int myHasher(std::string filename); 
};

