#include "EvolutionCore.h"
#include "EvolutionTime.h"
#include "EvolutionInput.h"
#include "EvolutionEffectManager.h"
#include "EvolutionSceneManager.h"
#include "EvolutionTextureManager.h"

EvolutionCore::EvolutionCore() 
{
	direct3D		= NULL;
	direct3DDevice	= NULL;
	console			= NULL;

	width	= 0;
	height	= 0;

	traceType = LOG;

	globalLightPosition = D3DXVECTOR3(-5000, 5000, -5000);

	windowed		= false;
	usingTrace		= true;
}

EvolutionCore::~EvolutionCore() 
{
}

EvolutionCore* EvolutionCore::GetInstance() 
{
	static EvolutionCore Instance;
	return &Instance;
}

void EvolutionCore::RegisterParameter(std::string applicationName, int width, int height, bool windowed, int traceType, bool usingTrace)
{
	this->applicationName	= applicationName;
	this->width				= width;
	this->height			= height;
	this->traceType			= traceType;
	this->windowed			= windowed;
	this->usingTrace		= usingTrace;
}

void EvolutionCore::Initialize()
{
	if (usingTrace)
	{
		if (traceType == LOG)
		{
			log = new EVLog;
		}
		else if (traceType == CONSOLE)
		{
			console = new EVConsole;
		}
	}

	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		WndProc,
		0L, 0L,
		GetModuleHandle(NULL),
		NULL, NULL, NULL, NULL,
		applicationName.c_str(),
		NULL };

	RegisterClassEx(&wc);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (windowed) 
	{
		int offsetX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		int offsetY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		hWnd = CreateWindow(
			applicationName.c_str(), applicationName.c_str(),
			WS_CAPTION | WS_SYSMENU, offsetX, offsetY, width, height,
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
			applicationName.c_str(), applicationName.c_str(),
			WS_EX_TOPMOST | WS_POPUP,
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

	direct3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	direct3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}

void EvolutionCore::ApplicationLoop() 
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
			Render();
		}
	}

	UnregisterClass(applicationName.c_str(), GetModuleHandle(NULL));
}

void EvolutionCore::Update() 
{
	EVTime->Update();
	EVInput->Update();
	EVSceneManager->Update();
}

void EvolutionCore::Render() 
{
	direct3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 80), 1.0f, 0);
	Update();
	if (SUCCEEDED(direct3DDevice->BeginScene())) 
	{
		EVSceneManager->Render();
		direct3DDevice->EndScene();
	}
	direct3DDevice->Present(0, 0, 0, 0);
}

void EvolutionCore::Release()
{
	direct3D->Release();
	direct3DDevice->Release();
	directSprite->Release();

	if (console)
	{
		delete console;
	}

	if (log)
	{
		delete log;
	}
}

LRESULT CALLBACK EvolutionCore::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg) 
	{
	case WM_DESTROY:
		
		PostQuitMessage(0);
		return 0;
		
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	if (msg == WM_MOUSEMOVE) 
	{
		EVInput->MouseMove(true);
	}
	else
	{
		EVInput->MouseMove(false);
	}

	return(DefWindowProc(hWnd, msg, wParam, lParam));
}