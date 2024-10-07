#ifndef _INGAMESCENE_H_
#define _INGAMESCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "MyJet.h"
#include "BulletManager.h"
#include "OtherBulletManager.h"
#include "MissileManager.h"
#include "Skybox.h"
#include "Water.h"
#include "HPForm.h"
#include "ScoreForm.h"
#include "Raider.h"
#include "ChatForm.h"
#include "TextBox.h"
#include "KillDeathInfo.h"
#include "KillLog.h"

class InGameScene : public Scene
{
public:
	InGameScene();
	~InGameScene();

	bool Initialize();

	void Update(float eTime);
	void Render();

	ChatForm* GetChatForm() { return chat; }

	MyJet* jet;
	Jet*	player[8];

	KillLog* killLog;

private:
	Camera* camera;

	BulletManager* bulletManager;
	OtherBulletManager* otherBulletManager;

	MissileManager* missileManager;

	Skybox* skybox;
	Water*	water;

	HPForm*		hp;
	ScoreForm*	score;
	Raider*		raider;

	ChatForm*	chat;
	TextBox*	textBox;

	KillDeathInfo* kdInfo;

	float ratioX;
	float ratioY;

	bool isChat;
};

#endif
