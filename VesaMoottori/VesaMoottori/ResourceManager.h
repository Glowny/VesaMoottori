#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>

typedef std::vector<unsigned char> DecodedImage;	// voitais käyttää projektissa enemmän

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void addImage(std::string filename,std::vector<unsigned char> image);	//dekoodattu kuva, name toimii keynä
	DecodedImage* findImage(std::string filename);
	void addImageLocation(std::string filename);	//kuvan sijainti vektoriin
private:
	std::map<unsigned int, DecodedImage> decodedImages; // imagelocationista kuva, joka dekoodataan ja pistetään tänne. Tämä ottaa myös nimen
	std::vector<std::string> imageLocations; // ei ehkä välttämätön; toisaalta voidaan tarkistaa onko jo upittu. Helppo muokattavuus jos vaikka tekstifilessä
	unsigned int myHasher(std::string filename); 
};

