#include "EvolutionSceneManager.h"

EvolutionSceneManager::EvolutionSceneManager()
{
	currentScene = NULL;
}

EvolutionSceneManager::~EvolutionSceneManager()
{

}

EvolutionSceneManager* EvolutionSceneManager::GetInstance()
{
	static EvolutionSceneManager instance;
	
	return &instance;
}

void EvolutionSceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void EvolutionSceneManager::Render()
{
	if (currentScene)
	{
		currentScene->Render();
	}
}

void EvolutionSceneManager::Release()
{
	if (currentScene)
	{
		delete currentScene;

		currentScene = NULL;
	}
}

void EvolutionSceneManager::ChangeScene(EVScene* scene, bool isErase)
{
	if (isErase)
	{
		delete currentScene;
	}

	currentScene = scene;
}