#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "lodepng.h"
class decode
{
public:
	std::vector<unsigned char> Decode1(const char* filename); // lataa fileen levylt‰ tiedostosijainnista, toimiiko stringill‰? jos ei voi teh‰ wrapperin t‰h‰n. t‰‰ vissiin on viel‰ png muodossa
	std::vector<unsigned char> Decode2(const char* filename); // decode to raw pixels in memory, eroa edelliseen ei hirveesti.
	std::vector<unsigned char> Decode3State(const char* filename); // state mukana, kai t‰t‰kin johonkin tarvii.
	static void Encode1(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height); // muutetaan png muotoon, mutta ei talleneta mihink‰‰n ( ei tee mit‰‰n atm);
	static void Encode2(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height); // tallenetaan levylle
	static void Encode3(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
private:
	decode();
	decode(const decode& dec);
	~decode();
	decode& operator =(const decode& dec);
};

