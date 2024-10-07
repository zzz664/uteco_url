#include <time.h>
#include "DirectX9.h"
#include "SceneManager.h"
#include "LoginScene.h"
#include "NicknameScene.h"
#include "LobbyScene.h"
#include "RoomScene.h"
#include "TestScene.h"
#include "InGameScene.h"
#include "SoundManager.h"
#include "Console.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Console* console = new Console();

	srand(time(NULL));
	DirectX9->SetParameter(L"DirectX9", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), true);
	DirectX9->Initialize();

	SceneManager->ChangeScene(new LoginScene);

	DirectX9->ApplicationLoop();

	delete console;
}