#include "RoomScene.h"
#include "DirectX9.h"
#include "InputManager.h"
#include "Automata.h"
#include "LobbyScene.h"
#include "InGameScene.h"
#include "SceneManager.h"
#include "Server\ServerManager.h"
#include "Def.h"

RoomScene::RoomScene(int roomId, bool isHost)
{

	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();
	
	AUTOMATA->SetEnable(false);
	AUTOMATA->SetEnableHangul(true);
	AUTOMATA->ClearBuffer();

	title = "";

	font = new Font("KoPub돋움체 Bold", 2, 30.0f);
	font->SetPosition(460 * ratioX, 120 * ratioY);
	font->SetColor(D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f));

	animationTime = 0.0f;

	this->isHost = isHost;

	isChangeScene = -1;

	toggleChat = false;

	this->roomId = roomId;

	{
		background[0] = new Sprite("Resource/Room/background.png");


		background[1] = new Sprite("Resource/Room/form-01.png");
		background[1]->SetPosition(0.0f, -1080 * ratioY);

		background[2] = new Sprite("Resource/Room/vs.png");
		background[2]->SetPosition(927 * ratioX, -780 * ratioY);

		background[3] = new Sprite("Resource/Room/teamleader_blank.png");
		background[3]->SetPosition(850 * ratioX, -650 * ratioY);

		for (int i = 0; i < 4; ++i) AddObject2D(background[i], false);
	}

	background[1]->AddChild(font);

	{
		for (int i = 0; i < 8; ++i)
		{
			slot[i] = new Slot(i, false);

			if (i < 4)
				slot[i]->SetPosition(0.0f, (60 * i + 150) * ratioY);
			else if (i > 3)
				slot[i]->SetPosition(1960.0f, (60 * (i - 4) + 150) * ratioY);

			AddObject2D(slot[i], false);

		}

	}

	{
		button[0] = new Button();
		button[0]->Initialize("Resource/Room/exit.png", NULL, L"", 0.0f);
		button[0]->SetPosition(-300.0f * ratioX, 420 * ratioY);
		AddObject2D(button[0]);

		button[1] = new Button();
		if (isHost)
		{
			button[1]->Initialize("Resource/Room/game_start.png", NULL, L"", 0.0f);
		}

		else
		{
			button[1]->Initialize("Resource/Room/ready.png", NULL, L"", 0.0f);
		}
		button[1]->SetPosition(1920 * ratioX, 420 * ratioY);
		AddObject2D(button[1]);
	}

	{
		textBox = new TextBox(0, "Resource/Room/chat_blank.png", 35.0f);
		textBox->Initialize("", 50, false);
		textBox->SetPosition(560 * ratioX, 1080 * ratioY);
	}

	{
		chatForm = new ChatForm("Resource/Room/chat_form.png", 20.0f);
		chatForm->SetPosition(520 * ratioX, 1080 * ratioY);
		AddObject2D(chatForm);
	}


	if (isHost)
	{
		slot[0]->SetHost(true);

		int size = wcslen(ServerManager::getInstance().NickName) * 2 + 1;
		char* charStr;
		charStr = new char[size];
		wcstombs(charStr, ServerManager::getInstance().NickName, size);
		slot[0]->SetSlotCaption(charStr);
		delete charStr;
	}

	isGetInfo = false;
}

RoomScene::~RoomScene()
{
	delete textBox;
}

void RoomScene::Update(float eTime)
{
	Scene::Update(eTime);

	static float t = 0.0f;

	if (OnLoadAnimation(eTime) == false)
	{
		t += eTime;

		if (t >= 0.5f && !isGetInfo)
		{
			isGetInfo = ServerManager::getInstance().GetReqInfo();
			t = 0.0f;
		}

		UpdateButton();
		UpdateChat(eTime);

		if (isChangeScene == 0)
		{
			ServerManager::getInstance().LeaveRoom();
			SceneManager->ChangeScene(new LobbyScene);
			return;
		}

		else if (isChangeScene == 1)
		{
			return;
		}
	}
}

void RoomScene::Render()
{
	for (int i = 0; i < 4; ++i) background[i]->Render();
	chatForm->Render();
	for (int i = 0; i < 8; ++i) slot[i]->Render();
	for (int i = 0; i < 2; ++i) button[i]->Render();
	textBox->Render();

	font->SetText(title.c_str());
	font->Render();
}

void RoomScene::ResetSlot(int index)
{
	slot[index]->SetSlotCaption("");
}

void RoomScene::UpdateButton()
{
	if (button[0]->MouseClick())
	{
		isChangeScene = 0;
		return;
	}

	if (button[1]->MouseClick())
	{
		//서버통신코드작성

		SceneManager->SetIsIngame(true);

		StartGame();

		//성공인경우 if문 안에 작성할코드 : isChangeScene = 1;
		//								  return;
		toggleChat = false;
		isChangeScene = 1;

		return;
	}
}

void RoomScene::UpdateChat(float eTime)
{
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		if (toggleChat == false)
		{
			toggleChat = true;
			return;
		}

		if (strlen(textBox->GetStringBuffer()) <= 0)
		{
			if (INPUT->GetKeyDown(VK_RETURN))
			{
				toggleChat = false;
				return;
			}
		}

		if (strlen(textBox->GetStringBuffer()) > 0)
		{
			ServerManager::getInstance().RoomChatting(textBox->GetStringBuffer_UNICODE());

			AUTOMATA->ClearBuffer();
			textBox->Reset("");
			AUTOMATA->ClearBuffer();
		}
	}

	if (toggleChat)
	{
		textBox->Update(eTime);
		AUTOMATA->SetEnable(true);
		textBox->SetFocus(true);
		textBox->Write();

		textBox->SetTextBoxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
	}

	else if (!toggleChat)
	{
		AUTOMATA->SetEnable(false);
		textBox->SetFocus(false);
		textBox->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

bool RoomScene::OnLoadAnimation(float eTime)
{
	if (animationTime < 0.1f && !isGetInfo)
	{
		isGetInfo = ServerManager::getInstance().GetReqInfo();
		SetIndex();
		return true;
	}

	if (animationTime >= 2.0f)
	{
		return false;
	}

	animationTime += eTime;

	background[1]->SmoothTranslate(D3DXVECTOR2(0.0f, 0.0f), 3 * eTime);
	background[2]->SmoothTranslate(D3DXVECTOR2(background[2]->GetPosition().x, 300 * ratioY), 3 * eTime);
	background[3]->SmoothTranslate(D3DXVECTOR2(background[3]->GetPosition().x, 430 * ratioY), 3 * eTime);
	for (int i = 0; i < 8; ++i)
	{
		if (i < 4)
		{
			slot[i]->SmoothTranslate(D3DXVECTOR2(450 * ratioX, slot[i]->GetPosition().y), 3 * eTime);
		}

		else if (i > 3)
		{
			slot[i]->SmoothTranslate(D3DXVECTOR2(1200 * ratioX, slot[i]->GetPosition().y), 3 * eTime);

		}
	}
	button[0]->SmoothTranslate(D3DXVECTOR2(51 * ratioX, button[0]->GetPosition().y), 3 * eTime);
	button[1]->SmoothTranslate(D3DXVECTOR2(1249 * ratioX, button[1]->GetPosition().y), 3 * eTime);

	chatForm->SmoothTranslate(D3DXVECTOR2(chatForm->GetPosition().x, 580 * ratioY), 3 * eTime);

	textBox->SmoothTranslate(D3DXVECTOR2(textBox->GetPosition().x, 820 * ratioY), 3 * eTime);

	return true;
}

bool RoomScene::OnChangeAnimation(float eTime)
{
	if (animationTime >= 2.0f)
	{
		return false;
	}

	animationTime += eTime;

	background[1]->SmoothTranslate(D3DXVECTOR2(0.0f, -1080 * ratioY), 3 * eTime);
	background[2]->SmoothTranslate(D3DXVECTOR2(background[2]->GetPosition().x, -780 * ratioY), 3 * eTime);
	background[3]->SmoothTranslate(D3DXVECTOR2(background[3]->GetPosition().x, -650 * ratioY), 3 * eTime);
	for (int i = 0; i < 8; ++i)
	{
		if (i < 4)
		{
			slot[i]->SmoothTranslate(D3DXVECTOR2(0.0f, slot[i]->GetPosition().y), 3 * eTime);
		}

		else if (i > 3)
		{
			slot[i]->SmoothTranslate(D3DXVECTOR2(1920.0f, slot[i]->GetPosition().y), 3 * eTime);

		}
	}
	button[0]->SmoothTranslate(D3DXVECTOR2(-300 * ratioX, button[0]->GetPosition().y), 3 * eTime);
	button[1]->SmoothTranslate(D3DXVECTOR2(1920 * ratioX, button[1]->GetPosition().y), 3 * eTime);

	textBox->SmoothTranslate(D3DXVECTOR2(textBox->GetPosition().x, 1080 * ratioY), 3 * eTime);

	return true;
}

void RoomScene::StartGame()
{
	printf("Start GAME \n");
	ServerManager::getInstance().GameStart();
}

void RoomScene::SetIndex()
{
	std::string str = wstToStr(ServerManager::getInstance().NickName);

	for (int i = 0; i < 8; ++i)
	{
		if (!strcmp(str.c_str(), slot[i]->GetSlotCaption()))
		{
			ServerManager::getInstance().mySlot = i;
			break;
		}
	}
}