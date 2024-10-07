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
	//	�� �Լ��� �α�â�� ���ڷ� ���� ������ ����Ѵ�.
	//	ù��° ���� : �������� �Է°��� ex) Log("Log�Լ� ���� %d", 123); �̷������� �� �� ����
	void Log(LPSTR fmt, ...);

private:

	void Create();
	static LRESULT CALLBACK EVLogProc(HWND, UINT, WPARAM, LPARAM);

};

#endif