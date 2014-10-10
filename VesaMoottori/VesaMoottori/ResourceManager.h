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
	ResourceManager() {};
	~ResourceManager() {};

	void LoadImage(std::string filename);			// upitaan kuva mappiin
	DecodedImage* FindImage(std::string filename);	//heateaan kuva mapista
	void AddImageLocation(std::string filename);	// ei käytetä mihinkään atm. IGNORE

	char* LoadShader(std::string filename);	// palauttaa tällä hetkellä shaderin & uppii shadermappiin
	char* FindShader(std::string filename);		// palauttaa shaderin shadermapista
private:
	std::map<unsigned int, char*> shaders;		//shadermap
	std::map<unsigned int, DecodedImage> decodedImages; // imagelocationista kuva, joka dekoodataan ja pistetään tänne. Tämä ottaa myös nimen
	std::vector<std::string> imageLocations; // ei ehkä välttämätön. Helppo muokattavuus jos vaikka tekstifileessä, josta voidaan sitten hakea kaikki tarvittavat kuvat.
	unsigned int MyHasher(std::string filename);	//muuttaa stringin uchariksi;
};

