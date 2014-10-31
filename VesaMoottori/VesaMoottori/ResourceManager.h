#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include <vector>
#include <map>
#include <string>
#include "Image.h"
//typedef std::vector<unsigned char> DecodedImage;

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	bool LoadPicture(std::string fileName); // Lisätään kuva mappiin.
	Image* FindImage(std::string fileName); // Haeteaan kuva mapista.
	
	//void AddImageLocation(std::string filename);	//kuvan sijainti vektoriin, jos vaikka käynnistäessä la
	//char* LoadShader(std::string filename);		//palauttaa tällä hetkellä shaderin & uppii shadermappiin
	//char* FindShader(std::string filename);		//palauttaa shaderin shadermapista

	void CreateTexture(Image *image);
	GLuint GetTexture() { return texture; }
	char *ShaderReader(std::string fileName);

private:
	unsigned int MyHasher(std::string fileName); // Muuttaa stringin uchariksi.
	std::map<unsigned int, Image> decodedImages; // Sisältää ladatut kuvat.
	GLuint texture;
	
	//std::map<unsigned int, char*> shaders;			//shadermap
	//std::vector<std::string> imageLocations;			//ei ehkä välttämätön. Helppo muokattavuus jos vaikka tekstifileessä, josta voidaan sitten hakea kaikki tarvittavat kuvat.
};