#ifndef _EVOLUTIONLOG_H_
#define _EVOLUTIONLOG_H_

#include <Windows.h>

class EVLog 
{
private:

	HWND			hWnd;
	HWND			hWndList;

public:

	EVLog();
	~EVLog();

	//************************************<Description>***********************************************
	//	이 함수는 로그창에 인자로 들어온 정보를 출력한다.
	//	첫번째 인자 : 포맷으로 입력가능 ex) Log("Log함수 실행 %d", 123); 이런식으로 쓸 수 있음
	void Log(LPSTR fmt, ...);

private:

	void Create();
	static LRESULT CALLBACK EVLogProc(HWND, UINT, WPARAM, LPARAM);

};

#endif