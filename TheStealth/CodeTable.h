#ifndef _CODETABLE_H_
#define _CODETABLE_H_

class CodeTable
{

	/*
	CodeTable[X][0] == �ϼ���
	CodeTable[X][1] == ������
	CodeTable[X][2] == �����ڵ�
	*/

public:

	static unsigned short codeTable[11172][3];	//��~�R
	static unsigned short codeTable2[67][3];	//��~�� (���� �����ڵ� �κ��� ������)
	static unsigned short GetWansungCodeFromJohab(unsigned short CODE);
};

#endif