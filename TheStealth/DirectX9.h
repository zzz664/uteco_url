#ifndef _DIRECTX9_H_
#define _DIRECTX9_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

using namespace std;

#define DirectX9 _DirectX9::GetInstance()

class _DirectX9
{

private:

	LPDIRECT3D9			direct3D;
	LPDIRECT3DDEVICE9	direct3DDevice;
	LPD3DXSPRITE		directSprite;
	HWND				hWnd;

	LPCWSTR				applicationName;

	int					width;
	int					height;

	float				ratioX;
	float				ratioY;

	float				aspect;

	bool				windowed;

	D3DXVECTOR3			lightPosition;
	D3DXMATRIX			lightViewMatrix;
	D3DXMATRIX			lightProjectionMatrix;

	_DirectX9();

	void Update();
	void Render();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

public:

	~_DirectX9();

	static _DirectX9* GetInstance();

	void SetParameter(LPCWSTR applicationName, int width, int height, bool windowed);
	void Initialize();
	void ApplicationLoop();

public:

	LPDIRECT3DDEVICE9	GetDevice();
	LPD3DXSPRITE		GetSprite();
	HWND				GetHwnd();

	D3DXVECTOR3			GetLightPosition();
	void				SetLightPosition(float x, float y, float z);

	D3DXMATRIX			GetLightViewMatrix();
	D3DXMATRIX			GetLightProjectionMatrix();

	int					GetScreenWidth();
	int					GetScreenHeight();

	float				GetRatioX();
	float				GetRatioY();

	float				GetAspect();

	LPCWSTR				GetApplicationName();
};

#endif