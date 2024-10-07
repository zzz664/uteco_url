#include "EvolutionLog.h"
#include "EvolutionCore.h"
#include "EvolutionTime.h"

#include <stdio.h>
#include <time.h>

EVLog::EVLog()
{
	Create();

	Log("Evolution Log Started...");
}

EVLog::~EVLog()
{
	DestroyWindow(hWnd);
}

void EVLog::Log(LPSTR fmt, ...)
{
	char	buff[1024];
	char	date[128];
	char	time[128];

	_strdate(date);
	_strtime(time);

	vsprintf(buff, fmt, (char *)(&fmt + 1));

	sprintf(date, "[%s] : %s", time, buff);

	SendMessage(hWndList, LB_ADDSTRING, (WPARAM)0L, (LPARAM)date);
	UINT32 n = SendMessage(hWndList, LB_GETCOUNT, 0, 0L) - 1;
	SendMessage(hWndList, LB_SETCURSEL, (WPARAM)n, 0L);
}

void EVLog::Create()
{
	int			x, y, cx, cy;
	WNDCLASS	wc;
	RECT		rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)EVLog::EVLogProc;
	wc.cbClsExtra = 0;									
	wc.cbWndExtra = 0;									
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "EvolutionLog";

	RegisterClass(&wc);

	cx = 300;
	cy = EVSystem->Height();
	x = (GetSystemMetrics(SM_CXSCREEN) - cx) / 2 + EVSystem->Width() / 2 + cx / 2;
	y = (GetSystemMetrics(SM_CYSCREEN) - EVSystem->Height()) / 2;


	hWnd = CreateWindow("EvolutionLog", "Evolution - [Log]", WS_CAPTION | WS_POPUP, x, y, cx, cy, NULL, NULL, GetModuleHandle(NULL), NULL);
	GetClientRect(hWnd, &rc);
	hWndList = CreateWindow("LISTBOX", "", WS_CHILD | WS_VSCROLL, 0, 0, rc.right, rc.bottom, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(hWnd, SW_SHOW);
	ShowWindow(hWndList, SW_SHOW);
}

LRESULT CALLBACK EVLog::EVLogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}