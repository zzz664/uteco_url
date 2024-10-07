#ifndef _CODETABLE_H_
#define _CODETABLE_H_

class CodeTable
{

	/*
	CodeTable[X][0] == ¿Ï¼ºÇü
	CodeTable[X][1] == Á¶ÇÕÇü
	CodeTable[X][2] == À¯´ÏÄÚµå
	*/

public:

	static unsigned short codeTable[11172][3];	//°¡~ÆR
	static unsigned short codeTable2[67][3];	//¤¡~¤Ó (¾ÆÁ÷ À¯´ÏÄÚµå ºÎºÐÀº ¸øÇßÀ½)
	static unsigned short GetWansungCodeFromJohab(unsigned short CODE);
};

#endif