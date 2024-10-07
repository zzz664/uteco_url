#ifndef _EVOLUTIONSCENEMANAGER_H_
#define _EVOLUTIONSCENEMANAGER_H_

#include "EvolutionScene.h"

#define EVSceneManager EvolutionSceneManager::GetInstance()

class EvolutionSceneManager 
{
private:

	EVScene* currentScene;

	EvolutionSceneManager();

public:

	~EvolutionSceneManager();

	static EvolutionSceneManager* GetInstance();

	//************************************<Description>***********************************************
	//	�� �Լ��� ���� ���� ������Ʈ�� ȣ���ϴ� �Լ��̴�.
	void Update();

	//************************************<Description>***********************************************
	//	�� �Լ��� ���� ���� ������ ȣ���ϴ� �Լ��̴�.
	void Render();
	void Release();

	//************************************<Description>***********************************************
	//	�� �Լ��� ���� ���� ���ڷ� ���� ������ �ٲٴ� �Լ��̴�.
	void ChangeScene(EVScene* scene, bool isErase = true);

};

#endif