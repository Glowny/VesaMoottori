#pragma once
#include <map>
#include <string>
#include "Image.h"
#include "Texture.h"

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	char* LoadShader(std::string fileName, std::string shaderName);
	char* FindShader(std::string shaderName);
	Texture* CreateTexture(std::string pictureName, std::string textureName);
	Texture* FindTexture(std::string textureName);

private:
	std::map<unsigned int, Image> decodedImages; // Sis‰lt‰‰ ladatut kuvat.
	std::map<std::string, Texture*> textures;
	std::map<std::string, char*> shaders;

	Image* FindImage(std::string fileName); // Haeteaan kuva mapista.
	bool LoadPicture(std::string fileName); // Lis‰t‰‰n kuva mappiin.
	unsigned int MyHasher(std::string fileName); // Muuttaa stringin uchariksi.
	char* ShaderReader(std::string fileName);
};