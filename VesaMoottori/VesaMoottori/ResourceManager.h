#pragma once
#include <vector>
#include <map>
#include <string>
#include "ImageInfo.h"

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	void RLoadImage(std::string filename);			//upitaan kuva mappiin
	ImageInfo* FindImage(std::string filename);		//heateaan kuva mapista
	void AddImageLocation(std::string filename);	//kuvan sijainti vektoriin, jos vaikka käynnistäessä la
	char* LoadShader(std::string filename);			//palauttaa tällä hetkellä shaderin & uppii shadermappiin
	char* FindShader(std::string filename);			//palauttaa shaderin shadermapista

private:
	std::map<unsigned int, char*> shaders;				//shadermap
	std::map<unsigned int, ImageInfo> decodedImages;	//imagelocationista kuva, joka dekoodataan ja pistetään tänne. Tämä ottaa myös nimen
	std::vector<std::string> imageLocations;			//ei ehkä välttämätön. Helppo muokattavuus jos vaikka tekstifileessä, josta voidaan sitten hakea kaikki tarvittavat kuvat.
	unsigned int MyHasher(std::string filename);		//muuttaa stringin uchariksi;
};

//typedef std::vector<unsigned char> DecodedImage;	// Ei käytetä missään tällä hetkellä.