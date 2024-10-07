#include "KeyTable.h"

unsigned short KeyTable::englishTable[3][10] = 
{
	{ 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' },
	{ 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', NULL },
	{ 'Z', 'X', 'C', 'V', 'B', 'N', 'M', NULL, NULL, NULL }
};

std::string KeyTable::koreanTable[3][10] =
{
	{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" },
	{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "" },
	{ "��", "��", "��", "��", "��", "��", "��", "", "", "" }
};
