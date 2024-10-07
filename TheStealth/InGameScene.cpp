#include "InGameScene.h"
#include "Server\ServerManager.h"
#include "DataManager.h"
#include "Time.h"
#include "Automata.h"
#include "DirectX9.h"
#include "InputManager.h"
#include "ResultScene.h"

InGameScene::InGameScene()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	AUTOMATA->ClearBuffer();
	AUTOMATA->SetEnable(false);
	AUTOMATA->SetEnableHangul(true);

	isChat = false;

	camera = new Camera;
	jet = new MyJet(camera);
	AddObject(jet);

	jet->Initialize(100.0f, 30.0f, 180.0f);
	jet->SetPosition((ServerManager::getInstance().mySlot % 4 - 1.5) * 50.0f, 300.0f, (ServerManager::getInstance().mySlot / 4) * 3000.0f);
	if (ServerManager::getInstance().mySlot / 4)
	{
		jet->RotateLocalY(180.0f);
	}

	for (int i = 0; i < 4; ++i)
	{
		player[i] = new Jet(camera, 0);
		AddObject(player[i]);
		player[i]->SetPosition((i % 4 - 1.5) * 50.0f, 300.0f, (i / 4) * 3000.0f);
	}
	for (int i = 4; i < 8; ++i)
	{
		player[i] = new Jet(camera, 1);
		AddObject(player[i]);
		player[i]->SetPosition((i % 4 - 1.5) * 50.0f, 300.0f, (i / 4) * 3000.0f);
		player[i]->RotateLocalY(180.0f);
	}

	bulletManager = new BulletManager(camera, jet, player);
	otherBulletManager = new OtherBulletManager(camera, player);

	missileManager = new MissileManager(camera, jet, player);

	skybox = new Skybox(camera);
	skybox->Create();
	AddObject(skybox);
	water = new Water(camera, 100000.0f);
	AddObject(water);

	{
		hp = new HPForm();
		hp->SetPosition(50 * ratioX, 760 * ratioY);
		AddObject2D(hp);

		score = new ScoreForm();
		score->SetPosition(610 * ratioX, 0.0f);
		AddObject2D(score);

		DxObject* tmp[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

		raider = new Raider((DxObject*)jet, tmp);
		raider->SetPosition(1700 * ratioX, 40 * ratioY);
		AddObject2D(raider);

		chat = new ChatForm("Resource/Ingame/chat_form.png", 18.0f);
		chat->SetPosition(1450 * ratioX, 700 * ratioY);
		AddObject2D(chat);

		textBox = new TextBox(0, "Resource/Ingame/chat_blank.png", 18.0f);
		textBox->Initialize("", 50, false);
		textBox->SetPosition(1485 * ratioX, 950 * ratioY);
		AddObject2D(textBox, false);

		kdInfo = new KillDeathInfo();
		kdInfo->SetPosition(0.0f, 0.0f);
		AddObject2D(kdInfo);

		killLog = new KillLog();
		killLog->SetPosition(5.0f * ratioX, 90 * ratioY);
		AddObject2D(killLog);
	}

	ServerManager::getInstance().SetPlayer(jet);
}

InGameScene::~InGameScene()
{
	delete missileManager;
	delete otherBulletManager;
	delete bulletManager;
	delete camera;
}

bool InGameScene::Initialize()
{
	return true;
}

void InGameScene::Update(float eTime)
{
	raider->SetTarget((DxObject**)player);

	Scene::Update(eTime);

	if (jet->info.HP < 0.0f) { jet->info.HP = 0.0f; }
	hp->SetHP(jet->info.HP);	

	if (jet->spawn)
	{
		ServerManager::getInstance().Regen();
		jet->Initialize(100.0f, 30.0f, 180.0f);
		jet->SetPosition((ServerManager::getInstance().mySlot % 4 - 1.5) * 50.0f, 300.0f, (ServerManager::getInstance().mySlot / 4) * 3000.0f);
		if (ServerManager::getInstance().mySlot / 4)
		{
			jet->RotateLocalY(180.0f);
		}
		jet->spawn = false;
		jet->isDead = false;
		jet->info.HP = 100.0f;

		printf("Respawn Success\n");
	}

	for (int i = 0; i < 8; ++i)
	{
		if (player[i]->isExist)
		{
			player[i]->UpdatePosition(eTime);
		}
	}
	if (jet->isDead) { camera->SmoothTranslate(jet->GetPosition() + jet->GetUp() * 30.0f - jet->GetForward() * 50.0f, 1.0f, eTime); }
	else { camera->SmoothTranslate(jet->GetPosition() + jet->GetUp() * 6.0f - jet->GetForward() * 15.0f, 10.0f, eTime); }
	camera->SmoothRotate(jet->GetRotation(), 10.0f, eTime);

	bulletManager->Update(eTime);
	otherBulletManager->Update(eTime);
	missileManager->Update(eTime);

	if (!isChat)
	{
		if (INPUT->GetKeyDown(VK_RETURN))
		{
			isChat = true;
			textBox->SetFocus(true);
			AUTOMATA->SetEnable(true);
			return;
		}
	}

	if (isChat)
	{
		if (INPUT->GetKeyDown(VK_RETURN) && strcmp(textBox->GetStringBuffer(), "") == 0)
		{
			isChat = false;
			textBox->SetFocus(false);
			textBox->Reset("");
			AUTOMATA->ClearBuffer();
			AUTOMATA->SetEnable(false);
			return;
		}

		if (INPUT->GetKeyDown(VK_RETURN) && strcmp(textBox->GetStringBuffer(), "") == 1)
		{
			ServerManager::getInstance().RoomChatting(textBox->GetStringBuffer_UNICODE());

			AUTOMATA->ClearBuffer();
			textBox->Reset("");
			AUTOMATA->ClearBuffer();
		}

		textBox->Update(eTime);
		textBox->Write();
	}

	if (score->m <= 0 && score->s <= 0.0f)
	{
		SceneManager->ChangeScene(new ResultScene);
		SceneManager->SetScene(RESULT);
	}

	if (jet->GetPosition().y < 10.0f && jet->info.IsAlive)
	{
		jet->ProcessDamage(1.0f);
	}
}

void InGameScene::Render()
{
	skybox->Render();
	water->Render();

	for (int i = 0; i < 8; ++i)
	{
		if (player[i]->isExist)
		{
			player[i]->Render();
		}
	}

	bulletManager->Render();
	otherBulletManager->Render();
	missileManager->Render();

	jet->Render();

	hp->Render();
	score->Render();
	raider->Render();
	chat->Render();
	if (isChat) textBox->Render();
	kdInfo->Render();
	killLog->Render();
}