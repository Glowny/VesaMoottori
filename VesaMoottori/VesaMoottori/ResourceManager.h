#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>
#include <fstream>
#include "lodepng.h"

typedef std::vector<unsigned char> DecodedImage;	// voitais käyttää projektissa enemmän

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void loadImage(std::string filename);			// upitaan kuva mappiin
	DecodedImage* findImage(std::string filename);	//heateaan kuva mapista
	void addImageLocation(std::string filename);	//kuvan sijainti vektoriin
	char* shaderReader(std::string filename);	// palauttaa tällä hetkellä shaderin & uppii shadermappiin
	char* findShader(std::string filename);		// palauttaa shaderin shadermapista
private:
	std::map<unsigned int, char*> shaders;		//shadermap
	std::map<unsigned int, DecodedImage> decodedImages; // imagelocationista kuva, joka dekoodataan ja pistetään tänne. Tämä ottaa myös nimen
	std::vector<std::string> imageLocations; // ei ehkä välttämätön; toisaalta voidaan tarkistaa onko jo upittu. Helppo muokattavuus jos vaikka tekstifilessä
	unsigned int myHasher(std::string filename);	//muuttaa stringin uchariksi;

};

