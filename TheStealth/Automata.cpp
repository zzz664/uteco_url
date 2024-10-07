#include "Automata.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "InputManager.h"

Automata::Automata() : inStackIndex(0), keyInputMode(KOR_INPUT), tempHanState(HS_START),
	keyCode(0), outStackIndex(0), realKey(0), key(1), strIndex(0)
{
	StringBufferClear();
	ClearOutStack();
	Clear();

	isEnglish = true;
	isEnable = false;
	isEnableHangul = false;

	length = 0;
}

Automata::~Automata()
{
	StringBufferClear();
	ClearOutStack();
	Clear();
}

void Automata::ClearBuffer()
{
	StringBufferClear();
	BackSpace();
	BackSpace();
	length = 0;
}

void Automata::SetBuffer(char* buffer)
{
	ClearBuffer();
	memcpy(destStrBuffer, buffer, sizeof(char)* strlen(buffer) + 1);
	strIndex = strlen(buffer);
}

void Automata::Clear()
{
	inStackIndex = 0;
	keyInputMode = KOR_INPUT;
	tempHanState = HS_START;
	keyCode = 0;

	for (int i = 0; i < INSTACK_SIZE; i++)
	{
		inStack[i].currentHanState = HS_START;
		inStack[i].unionCode = 0;
		inStack[i].key = 0;
	}
}

void Automata::ClearOutStack()
{
	outStackIndex = 0;
	for (int i = 0; i < OUTSTACK_SIZE; i++)
	{
		outStack[i] = 0;
	}
}

unsigned short	Automata::GetUnionCode()
{
	if (inStackIndex)
	{
		return inStack[inStackIndex - 1].unionCode;
	}
}

unsigned short	Automata::GetConvertedUnionCode()//완성형으로 컨버트 된 코드를 얻는다.
{
	unsigned short JCode = GetUnionCode();						//조합된 조합형코드를 얻어온다.
	unsigned short WCode = CodeTable::GetWansungCodeFromJohab(JCode);	//얻어온 글자는 조합형이므로 완성형으로 변환한다.
	unsigned short RealCode = (WCode << 8) | (WCode >> 8);					//내부 바이트 정렬대로 바이트순을 바꾼다
	return RealCode;
}

void Automata::PrintStack()
{
	//인스택상태 표시
	if (inStackIndex)
	for (int i = 0; i < inStackIndex; i++)
	{
		unsigned short JCode = inStack[i].unionCode;				//조합된 조합형코드를 얻어온다.
		unsigned short WCode = CodeTable::GetWansungCodeFromJohab(JCode);	//얻어온 글자는 조합형이므로 완성형으로 변환한다.
		unsigned short RealCode = (WCode << 8) | (WCode >> 8);					//내부 바이트 정렬대로 바이트순을 바꾼다
		char buff[3] = { RealCode & 0x00ff, RealCode >> 8, 0 };					//출력을 위해 char형 변수에 저장한다.
		printf("%s-", buff);
	}

}

unsigned char* Automata::GetCodeTable()
{
	static unsigned char HanKeyboardTable[] = {
		//0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,  /*  !"#$%&' */ 
		//0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,  /* ()*+,-./ */ 
		//0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  /* 01234567 */ 
		//0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,  /* 89:;<=>? */ 
		//0x40, 0x41, 0x42, 0x43, 0x44, 0x86, 0x46, 0x47,  /* @ABCDEFG */ 
		//0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0xA6,  /* HIJKLMNO */ 
		//0xAC, 0x8A, 0x83, 0x53, 0x8C, 0x55, 0x56, 0x8F,  /* PQRSTUVW */ 
		//0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,  /* XYZ[\]^_ */ 
		//0x60, 0x88, 0xBA, 0x90, 0x8D, 0x85, 0x87, 0x94,  /* `abcdefg */ 
		//0xAD, 0xA5, 0xA7, 0xA3, 0xBD, 0xBB, 0xB4, 0xA4,  /* hijklmno */ 
		//0xAA, 0x89, 0x82, 0x84, 0x8B, 0xAB, 0x93, 0x8E,  /* pqrstuvw */ 
		//0x92, 0xB3, 0x91, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F   /* xyz{|}~  */ 

		//쌍미음을 요청하면 A를 돌려주는게 아니라 'ㅁ'을 돌려주도록 수정
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,  /*  !"#$%&' */
		0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,  /* ()*+,-./ */
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  /* 01234567 */
		0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,  /* 89:;<=>? */
		0x40, 0x88, 0xBA, 0x90, 0x8D, 0x86, 0x87, 0x94,  /* `ABCDEFG */
		0xAD, 0xA5, 0xA7, 0xA3, 0xBD, 0xBB, 0xB4, 0xA6,  /* HIJKLMNO */
		0xAC, 0x8A, 0x83, 0x84, 0x8C, 0xAB, 0x93, 0x8F,  /* PQRSTUVW */
		0x92, 0xB3, 0x91, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,  /* XYZ[\]^_ */
		0x60, 0x88, 0xBA, 0x90, 0x8D, 0x85, 0x87, 0x94,  /* `abcdefg */
		0xAD, 0xA5, 0xA7, 0xA3, 0xBD, 0xBB, 0xB4, 0xA4,  /* hijklmno */
		0xAA, 0x89, 0x82, 0x84, 0x8B, 0xAB, 0x93, 0x8E,  /* pqrstuvw */
		0x92, 0xB3, 0x91, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F   /* xyz{|}~  */
	};
	return HanKeyboardTable;
}
	
unsigned short Automata::ConvertKey(unsigned short Key)
{
	unsigned char* CodeTable = GetCodeTable();
	if (GetNowMode() == ENG_INPUT || Key <= 32 || Key > 127)
		return Key;
	else
		return CodeTable[Key - 32];
};

unsigned short Automata::JoongsungPair(unsigned char Old, unsigned char New)
{
	static unsigned char dJoongTable[7][3] = {
		{ 0xad, 0xa3, 0xae },   /* ㅗ, ㅏ, ㅘ */
		{ 0xad, 0xa4, 0xaf },   /* ㅗ, ㅐ, ㅙ */
		{ 0xad, 0xbd, 0xb2 },   /* ㅗ, ㅣ, ㅚ */
		{ 0xb4, 0xa7, 0xb5 },   /* ㅜ, ㅓ, ㅝ */
		{ 0xb4, 0xaa, 0xb6 },   /* ㅜ, ㅔ, ㅞ */
		{ 0xb4, 0xbd, 0xb7 },	/* ㅜ, ㅣ, ㅟ */
		{ 0xbb, 0xbd, 0xbc }	/* ㅡ, ㅣ, ㅢ */
	};

	int i;
	for (i = 0; i < 7; i++)
	{
		if (dJoongTable[i][0] == Old && dJoongTable[i][1] == New)
			return keyCode = dJoongTable[i][2];
	}
	return 0;
}

unsigned short Automata::JongsungPair(unsigned char Old, unsigned char New)
{
	static unsigned char dJongsungTable[11][3] = {
		{ 0x82, 0x8b, 0xc4 },    /* ㄱ, ㅅ*/
		{ 0x84, 0x8e, 0xc6 },    /* ㄴ, ㅈ*/
		{ 0x84, 0x94, 0xc7 },    /* ㄴ, ㅎ*/
		{ 0x87, 0x82, 0xca },    /* ㄹ, ㄱ*/
		{ 0x87, 0x88, 0xcb },    /* ㄹ, ㅁ*/
		{ 0x87, 0x89, 0xcc },    /* ㄹ, ㅂ*/
		{ 0x87, 0x8b, 0xcd },    /* ㄹ, ㅅ*/
		{ 0x87, 0x92, 0xce },    /* ㄹ, ㅌ*/
		{ 0x87, 0x93, 0xcf },    /* ㄹ, ㅍ*/
		{ 0x87, 0x94, 0xd0 },    /* ㄹ, ㅎ*/
		{ 0x89, 0x8b, 0xd4 }     /* ㅂ, ㅅ*/
	};
	int i;
	for (i = 0; i < 11; i++)
	{
		if (dJongsungTable[i][0] == Old && dJongsungTable[i][1] == New)
			return keyCode = dJongsungTable[i][2];
	}
	return 0;
}

int Automata::hanAutomata2(unsigned short Key, unsigned short UnconvertedKey)
{
	/*--------------------------------------------------------------------
	인수	: key = 입력된 키 코드
	반환값	: 한 글자의 조합이 끝나면 1을, 계속 조합중이면 0을, 완성된 글자의 코드는 입력 스택의 가장 마지막에서 구할 수 있다.
	동작	:
	--------------------------------------------------------------------*/

	CHARKIND chKind;
	bool bCanBeJongsung = false;
	/* 초성코드에 대응하는 종성 코드 */
	static unsigned char Cho2Jong[] = {
		0xc2,  /*  기역                 */
		0xc3,  /*  쌍기역               */
		0xc5,  /*  니은                 */
		0xc8,  /*  디귿                 */
		0x00,  /*  쌍디귿 (해당 없음)   */
		0xc9,  /*  리을                 */
		0xd1,  /*  미음                 */
		0xd3,  /*  비읍                 */
		0x00,  /*  상비읍 (해당 없음)   */
		0xd5,  /*  시옷                 */
		0xd6,  /*  쌍시옷               */
		0xd7,  /*  이응                 */
		0xd8,  /*  지읒                 */
		0x00,  /*  쌍지읒 (해당 없음)   */
		0xd9,  /*  치읓                 */
		0xda,  /*  키읔                 */
		0xdb,  /*  티읕                 */
		0xdc,  /*  피읖                 */
		0xdd   /*  히읗                 */
	};

	unsigned short	TempunionCode;
	unsigned short	OldKeyCode;
	unsigned short	UC_OldKeyCode;	// UC is Unconverted


	//자음인지 모음인지 판단
	if ((Key & 0x60) == 0x20)
	{
		chKind = VOWEL; //모음
		bCanBeJongsung = false;
	}
	else
	{
		chKind = CONSONANT;
		if (!(Key == 0x86 || Key == 0x8A || Key == 0x8F)) // ㄸ, ㅃ, ㅉ,은 받침으로 올 수 없다. 		
			bCanBeJongsung = true;
	}

	//만일 한글이 입력되고 있다면 이전에 저장된 스택에서 조합된 코드와 입력된 글쇠를 가져온다.
	if (tempHanState)
	{
		TempunionCode = inStack[inStackIndex - 1].unionCode;
		OldKeyCode = inStack[inStackIndex - 1].key;
		UC_OldKeyCode = inStack[inStackIndex - 1].unConvertedKey;
	}
	else
	{
		TempunionCode = 0x8441;
		OldKeyCode = 0;
		UC_OldKeyCode = 0;
	}
	keyCode = Key;

	//오토마타 코어 부분
	HAN_STATUS OldState = State();
	switch (tempHanState)
	{
	case HS_START:
		if (chKind == CONSONANT)
			tempHanState = HS_CHOSUNG;
		else
			tempHanState = HS_JOONGSUNG;
		break;
	case HS_CHOSUNG:
		if (chKind == VOWEL)
			tempHanState = HS_JOONGSUNG;
		else
			tempHanState = HS_END1;
		break;
	case HS_JOONGSUNG:
		if (bCanBeJongsung)
			tempHanState = HS_JONGSUNG;
		else if (JoongsungPair(OldKeyCode, keyCode))
			tempHanState = HS_DJOONGSUNG;
		else
			tempHanState = HS_END1;
		break;
	case HS_DJOONGSUNG:
		if (bCanBeJongsung)
			tempHanState = HS_JONGSUNG;
		else
			tempHanState = HS_END1;
		break;
	case HS_JONGSUNG:
		if (chKind == CONSONANT && JongsungPair(OldKeyCode, keyCode))
			tempHanState = HS_DJONGSUNG;
		else if (chKind == VOWEL)
			tempHanState = HS_END2;
		else
			tempHanState = HS_END1;
		break;
	case HS_DJONGSUNG:
		if (chKind == VOWEL)
			tempHanState = HS_END2;
		else
			tempHanState = HS_END1;
		break;
	}

	//오토마타의 상태를 보고 코드를 조합한다.
	switch (tempHanState)
	{
	case HS_CHOSUNG:
		TempunionCode = (TempunionCode & 0x83FF) | ((keyCode - 0x80) << 10);
		break;
	case HS_JOONGSUNG:
	case HS_DJOONGSUNG:
		TempunionCode = (TempunionCode & 0xFC1F) | ((keyCode - 0xA0) << 5);
		if (OldState == HS_START)
		{
			inStack[inStackIndex].currentHanState = tempHanState;
			inStack[inStackIndex].unionCode = TempunionCode;
			inStack[inStackIndex].unConvertedKey = UnconvertedKey;
			inStack[inStackIndex++].key = Key;
			tempHanState = HS_START;
			return true;
		}
		break;
	case HS_JONGSUNG:
		keyCode = Cho2Jong[keyCode - 0x82];
	case HS_DJONGSUNG:
		TempunionCode = (TempunionCode & 0xFFE0) | (keyCode - 0xC0);
		break;
	case HS_END1:
		tempHanState = HS_START;
		//hanAutomata2(Key);
		outStack[outStackIndex++] = UnconvertedKey;
		return true;
	case HS_END2:
		tempHanState = HS_START;
		outStack[outStackIndex++] = UnconvertedKey;
		outStack[outStackIndex++] = UC_OldKeyCode;
		inStackIndex--;
		return true;
	}
	inStack[inStackIndex].currentHanState = tempHanState;
	inStack[inStackIndex].unionCode = TempunionCode;
	inStack[inStackIndex].unConvertedKey = UnconvertedKey;
	inStack[inStackIndex++].key = Key;
	return false;
}

int	Automata::BackSpace()
{
	switch (tempHanState)
	{
	case HS_START:
		return 0;
	case HS_CHOSUNG:
		tempHanState = HS_START;
		break;
	case HS_JOONGSUNG:
		tempHanState = HS_CHOSUNG;
		break;
	case HS_DJOONGSUNG:
		tempHanState = HS_JOONGSUNG;
		break;
	case HS_JONGSUNG:
		tempHanState = HS_JOONGSUNG;
		break;
	case HS_DJONGSUNG:
		tempHanState = HS_JONGSUNG;
		break;
	}

	inStackIndex--;

	length--;

	if (length <= 0)
	{
		length = 0;
	}

	return inStack[inStackIndex].unionCode;
}

int	Automata::AnotherKey()
{
	switch (tempHanState)
	{
	case HS_START:
		return 0;
	case HS_CHOSUNG:
	case HS_JOONGSUNG:
	case HS_DJOONGSUNG:
	case HS_JONGSUNG:
	case HS_DJONGSUNG:
		tempHanState = HS_START;
	}
	for (int i = 0; i < INSTACK_SIZE; i++)
	{
		inStack[i].currentHanState = HS_START;
		inStack[i].unionCode = 0;
		inStack[i].key = 0;
	}
	inStackIndex = 0;
	keyCode = 0;
	return true;
}
	
int Automata::IsHangul(char* Str, int Index)
{
	int State; // Eng = 0, Han 1st =1, Han 2nd =2
	int inMode;
	unsigned short Key;
	int i = 0;
	if (strlen(Str) < Index + 1)
		return -1;
	State = 0;
	while ((Key = *(Str + i)) != '\0')
	{
		if (Key < 0xa4a1)
			inMode = 0;
		else
			inMode = 1;

		switch (State)
		{
		case 0: //Eng
			if (inMode)	State = 1;
			else		State = 0;
			break;
		case 1:
			State = 2;
			break;
		case 2:
			if (inMode)	State = 1;
			else		State = 0;
			break;
		}

		if (i++ == Index)
			break;
	}
	return State;
}

void	Automata::StringBufferClear()
{
	memset(destStrBuffer, 0, STRINGBUFFER_SIZE + 1);
	strIndex = 0;
}

void Automata::Update()
{

	if (isEnableHangul)
	{
		if (INPUT->GetKey(VK_LCONTROL))
		{
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				isEnglish = !isEnglish;
				BackSpace();
			}
		}
	}
}

int Automata::KeyPush(int KeyInput)
{
	int RealKey = KeyInput;
	int ConvertedKey = ConvertKey(RealKey);							//처리할게 없으면 새로운 키를 입력받는다.
	bool bUnionComplated = false;

	if (!isEnglish)
	{
		if (RealKey == ConvertedKey)										// 한글입력 이외의 키를 입력받았다.
		{
			if (RealKey == 8)											//백스페이스 일 경우
			{
				if (BackSpace() == false)								//더 지울 조합이 없다. (오토마타가 HS_START 상태가 됨)
				{
					if (strIndex)
					{
						if (IsHangul(destStrBuffer, strIndex - 1))
							destStrBuffer[--strIndex] = 0;
						destStrBuffer[--strIndex] = 0;
					}
				}
			}
			else														//영어나 기타 특수문자가 눌렸을 경우
			{
				if (tempHanState)										//조합중인 문자가 있었다면..
				{
					unsigned short RealCode = GetConvertedUnionCode();
					destStrBuffer[strIndex++] = RealCode & 0x00ff;
					destStrBuffer[strIndex++] = RealCode >> 8;
				}
				destStrBuffer[strIndex++] = ConvertedKey;
				AnotherKey();
			}
		}
		else if (hanAutomata2(ConvertedKey, RealKey))					//글자가 완성될 때 마다 True를 리턴한다.
		{
			bUnionComplated = true;
			unsigned short RealCode = GetConvertedUnionCode();
			destStrBuffer[strIndex++] = RealCode & 0x00ff;
			destStrBuffer[strIndex++] = RealCode >> 8;
			length++;
			Clear();
		}
	}

	if (isEnglish)
	{
		if (RealKey == 8)											//백스페이스 일 경우
		{
			if (BackSpace() == false)								//더 지울 조합이 없다. (오토마타가 HS_START 상태가 됨)
			{
				if (strIndex)
				{
					if (IsHangul(destStrBuffer, strIndex - 1))
						destStrBuffer[--strIndex] = 0;
					destStrBuffer[--strIndex] = 0;
				}
			}
		}
		else														//영어나 기타 특수문자가 눌렸을 경우
		{
			destStrBuffer[strIndex++] = KeyInput;
			length++;
			AnotherKey();
		}
	}

	if (outStackIndex)												//최근 입력에서 초과되어 처리해야할 키가 남아있다면 재귀호출
	{
		RealKey = outStack[--outStackIndex];					//새로 입력받지말고 그것으로 한다.			
		return KeyPush(RealKey);
	}

	return bUnionComplated;
}

