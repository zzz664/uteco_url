#include "DirectX9.h"
#include "Automata.h"
#include "Time.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Server\ServerManager.h"
#include "DataManager.h"
#include "Server\TCPReader.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LPCWSTR title = L"DirectX9";

_DirectX9::_DirectX9()
{
	direct3D = 0;
	direct3DDevice = 0;
	directSprite = 0;

	applicationName = title;

	width = 0;
	height = 0;

	ratioX = GetSystemMetrics(SM_CXSCREEN) / 1920.0f;
	ratioY = GetSystemMetrics(SM_CYSCREEN) / 1080.0f;

	aspect = (float)GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);

	windowed = false;
}

_DirectX9::~_DirectX9()
{
	if (direct3D)
		direct3D->Release();

	if (direct3DDevice)
		direct3DDevice->Release();

	if(directSprite)
		directSprite->Release();

	SceneManager->Release();
}

_DirectX9* _DirectX9::GetInstance()
{
	static _DirectX9 instance;
	return &instance;
}

void _DirectX9::Update()
{
	AUTOMATA->Update();

	TIME->Update();
	INPUT->Update();
	SOUND->Update();
	
	SceneManager->Update(TIME->DeltaTime());

	Render();

	SceneManager->UpdateScene();
}

void _DirectX9::Render()
{
	direct3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 80), 1.0f, 0);
	if (SUCCEEDED(direct3DDevice->BeginScene()))
	{
		SceneManager->Render();
		direct3DDevice->EndScene();
	}
	direct3DDevice->Present(0, 0, 0, 0);
}

void _DirectX9::SetParameter(LPCWSTR applicationName, int width, int height, bool windowed)
{
	this->applicationName	= applicationName;
	this->width				= width;
	this->height			= height;
	this->windowed			= windowed;

	aspect = (float)width / height;
}

void _DirectX9::Initialize()
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		WndProc,
		0L, 0L,
		GetModuleHandle(NULL),
		NULL, NULL, NULL, NULL,
		applicationName,
		NULL };

	RegisterClassEx(&wc);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (windowed)
	{
		int offsetX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		int offsetY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		hWnd = CreateWindow(
			applicationName, applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, offsetX, offsetY, width, height,
			GetDesktopWindow(), NULL, wc.hInstance, NULL);

		direct3D = Direct3DCreate9(D3D_SDK_VERSION);

		d3dpp.Windowed = true;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.EnableAutoDepthStencil = true;
	}

	else
	{
		hWnd = CreateWindow(
			applicationName, applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			GetDesktopWindow(), NULL, wc.hInstance, NULL);

		direct3D = Direct3DCreate9(D3D_SDK_VERSION);

		d3dpp.Windowed = false;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferWidth = GetSystemMetrics(SM_CXSCREEN);
		d3dpp.BackBufferHeight = GetSystemMetrics(SM_CYSCREEN);
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.EnableAutoDepthStencil = true;
	}

	direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &direct3DDevice);

	D3DXCreateSprite(direct3DDevice, &directSprite);

	direct3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	direct3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	lightPosition = D3DXVECTOR3(-500.0f, 500.0f, -150.0f);

	D3DXVECTOR3 lookAt	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(
		&lightViewMatrix, &lightPosition, &lookAt, &up);

	D3DXMatrixPerspectiveFovLH(
		&lightProjectionMatrix, 0.25f * D3DX_PI, 1.0f, 5.0f, 12.0f);

	
	SOUND->Initialize();

	SOUND->AddSound2D(SOUND->BACKGROUND, FMOD_LOOP_NORMAL, "Resource/Sound/background.mp3");
	SOUND->AddSound3D(SOUND->JET, FMOD_LOOP_NORMAL, "Resource/Sound/jet.mp3", 50.0f, 5000.0f);
	SOUND->AddSound2D(SOUND->HEATSEEKING, FMOD_LOOP_NORMAL, "Resource/Sound/HeatSeeking.wav");
	SOUND->AddSound2D(SOUND->LOCKON, FMOD_LOOP_NORMAL, "Resource/Sound/LockOn.wav");
	SOUND->AddSound3D(SOUND->MISSILE, FMOD_LOOP_OFF, "Resource/Sound/Missile.wav", 50.0f, 3000.0f);
}

void _DirectX9::ApplicationLoop()
{
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			Update();
		}
	}
	UnregisterClass(title, GetModuleHandle(NULL));

	SAFE_DELETE(DATAMANAGER.thread_);
	ServerManager::getInstance().Release();
}

LRESULT CALLBACK _DirectX9::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CHAR:
		if (AUTOMATA->GetEnable())
		{
			if (wParam != '\t' && wParam != VK_RETURN)
			{
				AUTOMATA->KeyPush(wParam);
			}
		}
		break;

	case WM_MOUSEMOVE:
		INPUT->UpdateMousePosition(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE :
		DestroyWindow(hWnd);
		return 0;
	}

	return(DefWindowProc(hWnd, msg, wParam, lParam));
}

LPDIRECT3DDEVICE9 _DirectX9::GetDevice()
{
	return direct3DDevice;
}

LPD3DXSPRITE _DirectX9::GetSprite()
{
	return directSprite;
}

HWND _DirectX9::GetHwnd()
{
	return hWnd;
}

int _DirectX9::GetScreenWidth()
{
	return width;
}

int _DirectX9::GetScreenHeight()
{
	return height;
}

float _DirectX9::GetRatioX()
{
	return ratioX;
}

float _DirectX9::GetRatioY()
{
	return ratioY;
}

float _DirectX9::GetAspect()
{
	return aspect;
}

LPCWSTR _DirectX9::GetApplicationName()
{
	return applicationName;
}

void _DirectX9::SetLightPosition(float x, float y, float z)
{
	lightPosition.x = x;
	lightPosition.y = y;
	lightPosition.z = z;

	D3DXVECTOR3 lookAt	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(
		&lightViewMatrix, &lightPosition, &lookAt, &up);
}

D3DXVECTOR3 _DirectX9::GetLightPosition()
{
	return lightPosition;
}

D3DXMATRIX _DirectX9::GetLightViewMatrix()
{
	return lightViewMatrix;
}

D3DXMATRIX _DirectX9::GetLightProjectionMatrix()
{
	return lightProjectionMatrix;
}