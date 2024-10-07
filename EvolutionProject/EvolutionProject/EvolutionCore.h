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
	//	�� �Լ��� ������ ������ ���� ���ڵ��� ����ϴ� �Լ��̴�.
	//	ù��° ���� : ������ �̸�
	//	�ι�° ���� : ������ ���� ũ�� (windowed�� false�̸� �ƹ����̳� ��� �������)
	//	����° ���� : ������ ���� ũ�� (windowed�� false�̸� �ƹ����̳� ��� �������)
	//	�׹�° ���� : â��� ���� (false�Ͻ� ��üȭ��)
	//	�ټ���° ���� : trace�� ����� Ÿ�� [CONSOLE, LOG] (�⺻�� : LOG)
	//	������° ���� : �ܼ� �Ǵ� �α� ��뿩�� (�⺻�� : true)
	void RegisterParameter(std::string, int, int, bool, int traceType = LOG, bool usingTrace = true);

	//************************************<Description>***********************************************
	//	�� �Լ��� ��ϵ� ������ ���ؼ� �����츦 �����ϰ� DirectX�� �ʱ�ȭ�ϴ� �Լ��̴�.
	void Initialize();

	//************************************<Description>***********************************************
	//	������â�� ������ �ʵ��� �ϱ� ���� �Լ��̸� ���α׷����� �߻���
	//	�޼������� ó���ϴ� ���ҵ� �ϴ� �Լ��̴�.
	void ApplicationLoop();

public:

	//************************************<Description>***********************************************
	//	�������� ���� ũ�⸦ ��ȯ�ϴ� �Լ��̴�.
	int					Width()				{ return width; }

	//************************************<Description>***********************************************
	//	�������� ���� ũ�⸦ ��ȯ�ϴ� �Լ��̴�.
	int					Height()			{ return height; }

	//************************************<Description>***********************************************
	//	���� �������� �ڵ��� ��ȯ�ϴ� �Լ��̴�.
	HWND				Hwnd()				{ return hWnd; }

	//************************************<Description>***********************************************
	//	�������� �̸��� stringŸ������ ��ȯ�ϴ� �Լ��̴�.
	std::string			ApplicationName()	{ return applicationName; }

	//************************************<Description>***********************************************
	//	Direct3D ��ġ�� �����͸� ��ȯ�ϴ� �Լ��̴�.
	LPDIRECT3DDEVICE9	DirectDevice()		{ return direct3DDevice; }

	LPD3DXSPRITE		DirectSprite()		{ return directSprite; }

	//************************************<Description>***********************************************
	//	Evolution Engine�� �ִ� SystemLog�� �����͸� ��ȯ�ϴ� �Լ��̴�.
	EVLog*				SystemLog()			{ return log; }

public:

	void				GlobalLightPosition(D3DXVECTOR3 position)	{ globalLightPosition = position; }
	D3DXVECTOR3			GlobalLightPosition()						{ return globalLightPosition; }

};

#endif