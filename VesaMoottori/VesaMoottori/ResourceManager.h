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

	bool LoadPicture(std::string filename);			// Lis�t��n kuva mappiin.
	DecodedImage* FindImage(std::string filename);	// Haeteaan kuva mapista.
	
	//void AddImageLocation(std::string filename);	//kuvan sijainti vektoriin, jos vaikka k�ynnist�ess� la
	//char* LoadShader(std::string filename);		//palauttaa t�ll� hetkell� shaderin & uppii shadermappiin
	//char* FindShader(std::string filename);		//palauttaa shaderin shadermapista

private:
	unsigned int MyHasher(std::string filename);		// Muuttaa stringin uchariksi.
	std::map<unsigned int, DecodedImage> decodedImages;	// Sis�lt�� ladatut kuvat.
	
	//std::map<unsigned int, char*> shaders;			//shadermap
	//std::vector<std::string> imageLocations;			//ei ehk� v�ltt�m�t�n. Helppo muokattavuus jos vaikka tekstifileess�, josta voidaan sitten hakea kaikki tarvittavat kuvat.
};