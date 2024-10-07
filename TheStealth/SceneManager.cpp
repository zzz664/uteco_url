#include "SceneManager.h"
#include "InGameScene.h"
#include "LobbyScene.h"
#include "LoginScene.h"
#include "RoomScene.h"
#include "..\Core\DXUT.h"
#include "..\LowLib\Log.h"

_SceneManager::_SceneManager()
{
	currentScene = 0;
	currentSceneNum = 0;
	nextScene = 0;
	isIngame = false;
}

_SceneManager::~_SceneManager()
{

}

_SceneManager* _SceneManager::GetInstance()
{
	static _SceneManager instance;
	return &instance;
}

void _SceneManager::Update(float eTime)
{
	if (currentScene)
	{
		currentScene->Update(eTime);
	}
}

void _SceneManager::Render()
{
	if (currentScene)
	{
		currentScene->Render();
	}
}

void _SceneManager::Release()
{
	if (currentScene)
	{
		delete currentScene;
	}
}

void _SceneManager::SetScene(int scene)
{
	nextScene = scene;
}

void _SceneManager::UpdateScene()
{
	if (currentSceneNum != nextScene)
	{
		switch (nextScene)
		{
		case INGAME :
			ChangeScene(new InGameScene());
			currentSceneNum = INGAME;
		}
	}
}

void _SceneManager::ChangeScene(Scene* scene, bool isErase)
{
	if (isErase)
	{
		delete currentScene;
	}

	currentScene = scene;
}