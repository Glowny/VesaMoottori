#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <sstream>
#include <string>

class Debugger
{
public:
	Debugger& operator << (const std::string& s) { std::cout << s; return *this; };
	Debugger& operator << (long long l);			//Kaikki int muuttujat
	Debugger& operator << (unsigned long long l);	//Kaikki unsigned int muuttujat

	template <typename T>
	Debugger& operator << (const T& val)		//Kaikki muut muuttujat ostringstreamilla
	{
		std::ostringstream o;
		o << val;
		*this << o.str();
		return *this;
	}
};

#endif