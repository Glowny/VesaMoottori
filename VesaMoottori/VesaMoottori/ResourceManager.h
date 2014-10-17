#pragma once
#include <vector>
#include <map>
#include <string>

typedef std::vector<unsigned char> DecodedImage;

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	bool LoadPicture(std::string filename);			// Lisätään kuva mappiin.
	DecodedImage* FindImage(std::string filename);	// Haeteaan kuva mapista.
	
	//void AddImageLocation(std::string filename);	//kuvan sijainti vektoriin, jos vaikka käynnistäessä la
	//char* LoadShader(std::string filename);		//palauttaa tällä hetkellä shaderin & uppii shadermappiin
	//char* FindShader(std::string filename);		//palauttaa shaderin shadermapista

private:
	unsigned int MyHasher(std::string filename);		// Muuttaa stringin uchariksi.
	std::map<unsigned int, DecodedImage> decodedImages;	// Sisältää ladatut kuvat.
	
	//std::map<unsigned int, char*> shaders;			//shadermap
	//std::vector<std::string> imageLocations;			//ei ehkä välttämätön. Helppo muokattavuus jos vaikka tekstifileessä, josta voidaan sitten hakea kaikki tarvittavat kuvat.
};