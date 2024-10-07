#ifndef _EVOLUTIONCONSOLE_H_
#define _EVOLUTIONCONSOLE_H_

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <Windows.h>

class EVConsole 
{
public:

	EVConsole() 
	{
		int hCrt;
		FILE *hf;

		AllocConsole();

		hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "w");

		*stdout = *hf;
		setvbuf(stdout, NULL, _IONBF, 0);
	}

	~EVConsole() 
	{
		_fcloseall();
		FreeConsole();
	}
};

#endif