#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>
#include <fstream>
#include "lodepng.h"

typedef std::vector<unsigned char> DecodedImage;	// voitais k�ytt�� projektissa enemm�n

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};
	void loadImage(std::string filename);			// upitaan kuva mappiin
	DecodedImage* findImage(std::string filename);	//heateaan kuva mapista
	void addImageLocation(std::string filename);	//kuvan sijainti vektoriin
	char* loadShader(std::string filename);	// palauttaa t�ll� hetkell� shaderin & uppii shadermappiin
	char* findShader(std::string filename);		// palauttaa shaderin shadermapista
private:
	std::map<unsigned int, char*> shaders;		//shadermap
	std::map<unsigned int, DecodedImage> decodedImages; // imagelocationista kuva, joka dekoodataan ja pistet��n t�nne. T�m� ottaa my�s nimen
	std::vector<std::string> imageLocations; // ei ehk� v�ltt�m�t�n. Helppo muokattavuus jos vaikka tekstifileess�, josta voidaan sitten hakea kaikki tarvittavat kuvat.
	unsigned int myHasher(std::string filename);	//muuttaa stringin uchariksi;
};

