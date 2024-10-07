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
	//	이 함수는 현재 씬의 업데이트를 호출하는 함수이다.
	void Update();

	//************************************<Description>***********************************************
	//	이 함수는 현재 씬의 렌더를 호출하는 함수이다.
	void Render();
	void Release();

	//************************************<Description>***********************************************
	//	이 함수는 현재 씬을 인자로 들어온 씬으로 바꾸는 함수이다.
	void ChangeScene(EVScene* scene, bool isErase = true);

};

#endif