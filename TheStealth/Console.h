#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <Windows.h>

class Console
{
public:

	Console()
	{
		int hCrt;
		int hCrt2;
		FILE *hf;
		FILE *hf2;

		AllocConsole();

		hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		hCrt2 = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "w");
		hf2 = _fdopen(hCrt2, "r");

		*stdout = *hf;
		*stdin = *hf2;
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stdin, NULL, _IONBF, 0);
	}

	~Console()
	{
		_fcloseall();
		FreeConsole();
	}
};

#endif