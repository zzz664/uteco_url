#include "KeyTable.h"

unsigned short KeyTable::englishTable[3][10] = 
{
	{ 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' },
	{ 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', NULL },
	{ 'Z', 'X', 'C', 'V', 'B', 'N', 'M', NULL, NULL, NULL }
};

std::string KeyTable::koreanTable[3][10] =
{
	{ "げ", "じ", "ぇ", "ぁ", "さ", "に", "づ", "ち", "だ", "つ" },
	{ "け", "い", "し", "ぉ", "ぞ", "で", "っ", "た", "び", "" },
	{ "せ", "ぜ", "ず", "そ", "ば", "ぬ", "ぱ", "", "", "" }
};
