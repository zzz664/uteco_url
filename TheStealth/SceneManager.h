#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "Scene.h"

#define SceneManager _SceneManager::GetInstance()

#define LOGIN 0
#define LOBBY 1
#define ROOM 2
#define INGAME 3
#define RESULT 4

class _SceneManager
{
private:

	Scene* currentScene;
	int nextScene;
	bool isIngame;

private:

	_SceneManager();

public:

	~_SceneManager();

	static _SceneManager* GetInstance();

public:

	void Update(float eTime);
	void Render();
	void Release();

	void SetScene(int scene);
	void SetIsIngame(bool isIngame) { this->isIngame = isIngame; }
	bool GetIsIngame() { return isIngame; }
	void UpdateScene();
	void ChangeScene(Scene* scene, bool isErase = true);

	Scene* GetCurrentScene() { return currentScene; }

	int currentSceneNum;
};

#endif