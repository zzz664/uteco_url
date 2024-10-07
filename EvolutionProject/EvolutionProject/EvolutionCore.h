#ifndef _EVOLUTIONCORE_H_
#define _EVOLUTIONCORE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "EvolutionConsole.h"
#include "EvolutionLog.h"

#define EVSystem EvolutionCore::GetInstance()

#define LOG 0
#define CONSOLE 1

class EvolutionCore 
{

private:

	LPDIRECT3D9			direct3D;
	LPDIRECT3DDEVICE9	direct3DDevice;
	LPD3DXSPRITE		directSprite;
	HWND				hWnd;

	EVConsole*			console;
	EVLog*				log;

	D3DXVECTOR3			globalLightPosition;

	std::string			applicationName;

	int					width;
	int					height;

	int					traceType;

	bool				windowed;
	bool				usingTrace;

private:

	EvolutionCore();

	void Update();
	void Render();
	void Release();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

public:

	~EvolutionCore();

	static EvolutionCore* GetInstance();

	//************************************<Description>***********************************************
	//	이 함수는 윈도우 생성을 위한 인자들을 등록하는 함수이다.
	//	첫번째 인자 : 윈도우 이름
	//	두번째 인자 : 윈도우 가로 크기 (windowed가 false이면 아무값이나 적어도 상관없다)
	//	세번째 인자 : 윈도우 세로 크기 (windowed가 false이면 아무값이나 적어도 상관없다)
	//	네번째 인자 : 창모드 여부 (false일시 전체화면)
	//	다섯번째 인자 : trace로 사용할 타입 [CONSOLE, LOG] (기본값 : LOG)
	//	여섯번째 인자 : 콘솔 또는 로그 사용여부 (기본값 : true)
	void RegisterParameter(std::string, int, int, bool, int traceType = LOG, bool usingTrace = true);

	//************************************<Description>***********************************************
	//	이 함수는 등록된 정보를 통해서 윈도우를 생성하고 DirectX를 초기화하는 함수이다.
	void Initialize();

	//************************************<Description>***********************************************
	//	윈도우창이 꺼지지 않도록 하기 위한 함수이며 프로그램에서 발생한
	//	메세지들을 처리하는 역할도 하는 함수이다.
	void ApplicationLoop();

public:

	//************************************<Description>***********************************************
	//	윈도우의 가로 크기를 반환하는 함수이다.
	int					Width()				{ return width; }

	//************************************<Description>***********************************************
	//	윈도우의 세로 크기를 반환하는 함수이다.
	int					Height()			{ return height; }

	//************************************<Description>***********************************************
	//	현재 윈도우의 핸들을 반환하는 함수이다.
	HWND				Hwnd()				{ return hWnd; }

	//************************************<Description>***********************************************
	//	윈도우의 이름을 string타입으로 반환하는 함수이다.
	std::string			ApplicationName()	{ return applicationName; }

	//************************************<Description>***********************************************
	//	Direct3D 장치의 포인터를 반환하는 함수이다.
	LPDIRECT3DDEVICE9	DirectDevice()		{ return direct3DDevice; }

	LPD3DXSPRITE		DirectSprite()		{ return directSprite; }

	//************************************<Description>***********************************************
	//	Evolution Engine에 있는 SystemLog의 포인터를 반환하는 함수이다.
	EVLog*				SystemLog()			{ return log; }

public:

	void				GlobalLightPosition(D3DXVECTOR3 position)	{ globalLightPosition = position; }
	D3DXVECTOR3			GlobalLightPosition()						{ return globalLightPosition; }

};

#endif