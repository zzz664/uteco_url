#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

#include "CodeTable.h"

#define INSTACK_SIZE		1000
#define OUTSTACK_SIZE		1000
#define STRINGBUFFER_SIZE	1000

#define AUTOMATA Automata::GetInstance()

class Automata
{
private:

	enum KEYINPUTMODE { ENG_INPUT, KOR_INPUT };
	enum CHARKIND { CONSONANT, VOWEL }; //����, ����


	enum HAN_STATUS
	{
		HS_START,
		HS_CHOSUNG,
		HS_JOONGSUNG, HS_DJOONGSUNG,
		HS_JONGSUNG, HS_DJONGSUNG,
		HS_END1, HS_END2
	};


	struct INSTACKNODE
	{
		HAN_STATUS				currentHanState;
		unsigned short			unionCode;
		unsigned short			key;
		unsigned short			unConvertedKey;
	};

private:

	KEYINPUTMODE	keyInputMode;
	HAN_STATUS		tempHanState;

	int				inStackIndex;
	INSTACKNODE		inStack[INSTACK_SIZE];											//�������� ���ڸ� �����ϴ� Stack
	int				outStackIndex;
	unsigned short	outStack[OUTSTACK_SIZE];

	unsigned short	keyCode;
	int				realKey, key;
	char			destStrBuffer[STRINGBUFFER_SIZE];									// �Էµ� �ڷᰡ ����� ����	
	int				strIndex;															// �Է� ������	

	bool			isEnglish;
	bool			isEnable;
	bool			isEnableHangul;

	int				length;

private:

	Automata();

public:

	~Automata();

	static Automata* GetInstance() 
	{
		static Automata instance;
		return &instance;
	}

	void SetIsEnglish(bool isEnglish) { this->isEnglish = isEnglish; }

	void SetEnableHangul(bool enable) { isEnableHangul= enable; }
	bool GetEnableHangul() { return isEnableHangul; }

	int GetLength() { return length; }

	void SetEnable(bool enable) { isEnable = enable; }
	bool GetEnable() { return isEnable; }

public:
	int				KeyPush(int KeyInput);
	const char*		GetStringBuffer(void) const { return destStrBuffer; }				//���ڿ��� ����� ���۸� ���´�. (�ϼ������� ����Ǿ� ����)
	void			StringBufferClear();												//��Ʈ�� ���۸� �����.
	KEYINPUTMODE	ChangeKeyInputMode(KEYINPUTMODE Mode){ return keyInputMode = Mode; }//��/�� ��ȯ		
	int				GetBufferSize() { return STRINGBUFFER_SIZE; }						//��Ʈ�� ���� ũ�⸦ �� �� �ִ�.
	HAN_STATUS		State() const { return tempHanState; }								//���� �������� ���¸� �� �� �ִ�.

	unsigned short	GetConvertedUnionCode();											//�������� ���ڸ� �ϼ������� ����
	unsigned short	GetUnionCode();														//�������� ���ڸ� ���������� ����

	void PrintStack();				//ǥ��������� ���� ���¸� ����Ѵ�.

	void ClearBuffer();
	void Update();

	bool GetIsEnglish() { return isEnglish; }
	void SetBuffer(char* buffer);

private:
	void Clear();
	void ClearOutStack();	

	int IsHangul(char* Str, int Index);

	unsigned short	ConvertKey(unsigned short key);
	int	BackSpace();
	int	AnotherKey();

	unsigned char* GetCodeTable();
	unsigned short JoongsungPair(unsigned char Old, unsigned char New);
	unsigned short JongsungPair(unsigned char Old, unsigned char New);
	KEYINPUTMODE GetNowMode(void){ return keyInputMode; }

	//Return ��
	//	0 : ������
	//	1 : �ѱ��� �ϼ��Ǿ���
	//	2 : �ѱ��� �̿��� ���ڰ� ���յƴ�.
	//	3 : �齺���̽�
	int hanAutomata2(unsigned short Key, unsigned short UnconvertedKey);
};

#endif