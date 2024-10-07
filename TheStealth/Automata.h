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
	enum CHARKIND { CONSONANT, VOWEL }; //모음, 자음


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
	INSTACKNODE		inStack[INSTACK_SIZE];											//조합중인 글자를 저장하는 Stack
	int				outStackIndex;
	unsigned short	outStack[OUTSTACK_SIZE];

	unsigned short	keyCode;
	int				realKey, key;
	char			destStrBuffer[STRINGBUFFER_SIZE];									// 입력된 자료가 저장될 버퍼	
	int				strIndex;															// 입력 포인터	

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
	const char*		GetStringBuffer(void) const { return destStrBuffer; }				//문자열이 저장된 버퍼를 얻어온다. (완성형으로 저장되어 있음)
	void			StringBufferClear();												//스트링 버퍼를 지운다.
	KEYINPUTMODE	ChangeKeyInputMode(KEYINPUTMODE Mode){ return keyInputMode = Mode; }//한/영 전환		
	int				GetBufferSize() { return STRINGBUFFER_SIZE; }						//스트링 버퍼 크기를 알 수 있다.
	HAN_STATUS		State() const { return tempHanState; }								//현재 조합중인 상태를 알 수 있다.

	unsigned short	GetConvertedUnionCode();											//조합중인 글자를 완성형으로 얻어옴
	unsigned short	GetUnionCode();														//조합중인 글자를 조합형으로 얻어옴

	void PrintStack();				//표준출력으로 현재 상태를 출력한다.

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

	//Return 값
	//	0 : 조합중
	//	1 : 한글이 완성되었다
	//	2 : 한글이 이외의 문자가 조합됐다.
	//	3 : 백스페이스
	int hanAutomata2(unsigned short Key, unsigned short UnconvertedKey);
};

#endif