#ifndef _KEYTABLE_H_
#define _KEYTABLE_H_

#include <string>
#include <windows.h>

class KeyTable
{

public:
	static unsigned short englishTable[3][10];
	static std::string koreanTable[3][10];
};

#endif