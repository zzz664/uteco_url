#include "LobbyScene.h"
#include "Def.h"
#include "DirectX9.h"
#include "Automata.h"
#include "RoomScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Server\ServerManager.h"

LobbyScene::LobbyScene()
{
	animationTime = 0.0f;

	page = 0;
	maxPage = 0;

	roomId = -1;

	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	AUTOMATA->ClearBuffer();
	AUTOMATA->SetEnableHangul(true);
	AUTOMATA->SetEnable(false);

	isInLobby = false;
	isMakeRoom = false;
	isChangeScene = -1;

	font = new Font("KoPub돋움체 Bold", 2, 25.0f);
	font->SetPosition(0.0f, 120 * ratioY);

	{
		camera = new Camera();
		camera->MoveTo(0.0f, 100.0f, 0.0f);

		skybox = new Skybox(camera);
		skybox->Create();

		jet = new MyJet(camera);
		jet->Initialize(200.0f, 120.0f, 300.0f);
		jet->SetPosition(0.0f, 100.0f, 0.0f);

		water = new Water(camera, 100000.0f);
		water->SetNormalScale(0.25f);
		AddObject(skybox);
		AddObject(jet);
		AddObject(water);
	}

	{
		for (int i = 0; i < 4; ++i)
		{
			button[i] = new Button();
			button[i]->Initialize("Resource/Lobby/button.png", "Resource/Lobby/button_select.png", L"", 0.0f);
		
			button[i]->SetPosition(-200 * ratioX, i * button[i]->GetArea().bottom);

			button[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

			AddObject2D(button[i]);
		}
	}

	{
		icon[0] = new Sprite("Resource/Lobby/robby_icon.png");
		icon[1] = new Sprite("Resource/Lobby/makeroom_icon-01.png");
		icon[2] = new Sprite("Resource/Lobby/about_icon-01.png");
		icon[3] = new Sprite("Resource/Lobby/exit_icon-01.png");

		for (int i = 0; i < 4; ++i)
		{
			icon[i]->SetPosition(
				button[i]->GetPosition().x + button[i]->GetArea().right / 2 - icon[i]->GetWidth() / 2,
				button[i]->GetPosition().y + button[i]->GetArea().bottom / 2 - icon[i]->GetHeight() / 2);

			icon[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		for (int i = 0; i < 4; ++i) AddObject2D(icon[i], false);
	}

	{
		for (int i = 0; i < 7; ++i)
		{
			roomButton[i] = new RoomButton();
			
			roomButton[i]->SetPosition(2000 * ratioX, (i * 110 + 170) * ratioY);

			AddObject2D(roomButton[i]);
		}

		pageButton[0] = new Button();
		pageButton[1] = new Button();

		pageButton[0]->Initialize("Resource/Lobby/prev-01.png", NULL, L"", 0.0f);
		pageButton[1]->Initialize("Resource/Lobby/next-01.png", NULL, L"", 0.0f);

		pageButton[0]->SetPosition(2100 * ratioX, roomButton[6]->GetPosition().y + (120 * ratioY));
		pageButton[1]->SetPosition(3500 * ratioX, roomButton[6]->GetPosition().y + (120 * ratioY));

		for (int i = 0; i < 2; ++i) AddObject2D(pageButton[i]);
	}

	alert = new MakeRoomAlert();
	alert->SetPosition(600 * ratioX, -350 * ratioY);
	AddObject2D(alert, false);
}

LobbyScene::~LobbyScene()
{
	delete camera;

	roomInfo.clear();
}

void LobbyScene::Update(float eTime)
{
	Scene::Update(eTime);

	static float t = 1.0f;

	UpdateJet(eTime);

	if (OnLoadAnimation(eTime) == false)
	{
		OnAlertAnimation(eTime);

		UpdateButton(eTime);

		t += eTime;

		if (t >= 1.0f)
		{
			roomInfo.clear();

			ROOM_INFO_DATA rooms[10];
			ROOM_INFO_DATA *tmp;
			tmp = ServerManager::getInstance().GetRoomsInfo();
			memcpy(rooms, tmp, sizeof(ROOM_INFO_DATA)* 10);

			for (auto room : rooms)
			{
				wstring title = room.Title;
				if (title.length() <= 0) continue;
				if ((int)room.Index < 0) continue;

				DWORD index = room.Index;

				ROOM_INFO p;

				p.title = title;
				p.id = index;
				p.currentPerson = room.CurrentNum;
				p.maxPerson = 8;
				p.state = 0;

				roomInfo.push_back(p);
			}

			t = 0.0f;
		}

		if (isInLobby)
		{
			if (OnLobbyInAnimation(eTime) == false)
			{
	
				UpdateLobby();
			}
		}

		else
		{
			if (OnLobbyOutAnimation(eTime) == false)
			{
				//t = 0.0f;
			}
		}

		if (isChangeScene == 1)
		{
			SceneManager->ChangeScene(new RoomScene(roomInfo.size(), true));
			return;
		}

		else if (isChangeScene == 0)
		{
			SceneManager->ChangeScene(new RoomScene(roomId, false));
			return;
		}
	}
}

void LobbyScene::Render()
{
	skybox->Render();
	water->Render();
	jet->Render();

	for (int i = 0; i < 4; ++i) 
	{
		button[i]->Render();
		icon[i]->Render();
	}

	for (int i = 0; i < 7; ++i) roomButton[i]->Render(); 

	for (int i = 0; i < 2; ++i) pageButton[i]->Render();

	alert->Render();
	
	font->SetPosition(roomButton[0]->GetPosition().x + 30 * ratioX, 120 * ratioY);
	font->SetText("번호");
	font->Render();

	font->SetPosition(font->GetPosition().x + 165 * ratioX, font->GetPosition().y);
	font->SetText("방 이름");
	font->Render();

	font->SetPosition(font->GetPosition().x + (595 * ratioX), font->GetPosition().y);
	font->SetText("인원수");
	font->Render();

	font->SetPosition(font->GetPosition().x + (220 * ratioX), font->GetPosition().y);
	font->SetText("게임 상태");
	font->Render();

	font->SetPosition(roomButton[6]->GetPosition().x + (70 * ratioX), pageButton[0]->GetPosition().y + (8 * ratioY));
	font->SetText("PREV");
	font->Render();

	font->SetPosition(font->GetPosition().x + (500 * ratioX), font->GetPosition().y);
	font->SetText("%d / %d", (page + 1), (maxPage + 1));
	font->Render();

	font->SetPosition(roomButton[6]->GetPosition().x + (1030 * ratioX), pageButton[0]->GetPosition().y + (8 * ratioY));
	font->SetText("NEXT");
	font->Render();
}

void LobbyScene::UpdateLobby()
{
	if (roomInfo.size() != 0)
	{
		maxPage = ceil((roomInfo.size() - 1) / 7);
	}

	for (int i = 0; i < 7; ++i)
	{
		if ((i + page * 7) >= roomInfo.size())
		{
			break;
		}

		ROOM_INFO tmp = roomInfo[i + page * 7];

		roomButton[i]->SetRoom(tmp.id + 1, wstToStr(tmp.title.c_str()).c_str(), tmp.currentPerson, tmp.maxPerson, tmp.state);
	}

	for (int i = 0; i < 7; ++i)
	{
		if (roomButton[i]->MouseClick())
		{
			if (ServerManager::getInstance().EnterRoom(roomButton[i]->GetId() - 1))
			{
				isChangeScene = 0;
				roomId = roomButton[i]->GetId() - 1;
				return;
			}

			else
			{

			}
		}
	}
}

void LobbyScene::UpdateButton(float eTime)
{
	if (isMakeRoom) alert->Update(eTime);

	for (int i = 0; i < 4; ++i)
	{
		if (!isMakeRoom || i == 0 || i == 1)
		{
			if (button[i]->MouseOn())
			{
				button[i]->SmoothTranslate(D3DXVECTOR2(0.0f, button[i]->GetPosition().y), 0.5);
				icon[i]->SmoothTranslate(D3DXVECTOR2(91 * ratioX, icon[i]->GetPosition().y), 0.5);
			}

			else
			{
				button[i]->SmoothTranslate(D3DXVECTOR2(-200 * ratioX, button[i]->GetPosition().y), 0.5);
				icon[i]->SmoothTranslate(D3DXVECTOR2(-109 * ratioX, icon[i]->GetPosition().y), 0.5);
			}
		}
	}


	for (int i = 0; i < 2; ++i)
	{
		if (pageButton[i]->MouseOn())
		{
			pageButton[i]->SetButtonColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}

		else
		{
			pageButton[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	if (button[0]->MouseClick())
	{
		isInLobby = !isInLobby;
		isMakeRoom = false;
		AUTOMATA->SetEnable(false);
		if (!isMakeRoom)
		{
			AUTOMATA->ClearBuffer();
			alert->Reset();
		}
		animationTime = 0.0f;
	}

	if (button[2]->MouseClick() && !isMakeRoom)
	{

	}

	if (button[3]->MouseClick() && !isMakeRoom)
	{
		SendMessage(DirectX9->GetHwnd(), WM_DESTROY, NULL, NULL);
	}

	if (button[1]->MouseClick())
	{
		isMakeRoom = !isMakeRoom;
		isInLobby = false;
		AUTOMATA->SetEnable(isMakeRoom);
		if (!isMakeRoom)
		{
			AUTOMATA->ClearBuffer();
			alert->Reset();
		}
		animationTime = 0.0f;
	}

	if (isMakeRoom && alert->GetCancleClick())
	{
		isMakeRoom = false;
		AUTOMATA->SetEnable(false);
		animationTime = 0.0f;
	}

	if (isMakeRoom && (alert->GetOKClick() || INPUT->GetKeyDown(VK_RETURN)))
	{
		if (strlen(AUTOMATA->GetStringBuffer()) < 1)
		{
			alert->Reset();
		}

		else
		{
			if (ServerManager::getInstance().CreateRoom(alert->GetText()))
			{
				isChangeScene = 1;
				return;
			}

			else
			{

			}
		}
	}

	if (pageButton[0]->MouseClick())
	{
		for (int i = 0; i < 7; ++i) roomButton[i]->SetRoom(0, "", 0, 0, 0);
		page--;
		if (page <= 0)
		{
			page = 0;
		}
	}

	if (pageButton[1]->MouseClick())
	{
		for (int i = 0; i < 7; ++i) roomButton[i]->SetRoom(0, "", 0, 0, 0);
		page++;
		if (page >= maxPage)
		{
			page = maxPage;
		}
	}
}

void LobbyScene::UpdateJet(float eTime)
{
	camera->SmoothTranslate(jet->GetPosition() + jet->GetUp() * 6.0f - jet->GetForward() * 15.0f, 10.0f, eTime);
	camera->SmoothRotate(jet->GetRotation(), 10.0f, eTime);
}

bool LobbyScene::OnLoadAnimation(float eTime)
{
	static float accelation = 0.0f;

	if (accelation - 45 * eTime >= 1.0f)
	{
		for (int i = 0; i < 4; ++i)
		{
			button[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			icon[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		return false;
	}

	else
	{
		accelation += eTime;

		for (int i = 0; i < 4; ++i)
		{
			button[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation - (i * 15 * eTime)));
			icon[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation - (i * 15 * eTime)));
		}
	}

	return true;
}

bool LobbyScene::OnLobbyInAnimation(float eTime)
{
	if (animationTime >= 3.0f)
	{
		return false;
	}


	animationTime += eTime;

	int j = 7;
	for (int i = 0; i < 7; ++i, --j)
	{
		roomButton[i]->SmoothTranslate(D3DXVECTOR2(533 * ratioX, roomButton[i]->GetPosition().y), (j + 3) * eTime);
	}

	pageButton[0]->SmoothTranslate(D3DXVECTOR2(666 * ratioX, pageButton[0]->GetPosition().y), (j + 3) * eTime);
	pageButton[1]->SmoothTranslate(D3DXVECTOR2(1500 * ratioX, pageButton[1]->GetPosition().y), (j + 3) * eTime);

	return true;
}

bool LobbyScene::OnLobbyOutAnimation(float eTime)
{
	if (animationTime >= 3.0f)
	{
		return false;
	}

	animationTime += eTime;

	int j = 7;
	for (int i = 0; i < 7; ++i, --j)
	{
		roomButton[i]->SmoothTranslate(D3DXVECTOR2(2000 * ratioX, roomButton[i]->GetPosition().y), (j + 3) * eTime);
	}

	pageButton[0]->SmoothTranslate(D3DXVECTOR2(2100 * ratioX, pageButton[0]->GetPosition().y), (j + 3) * eTime);
	pageButton[1]->SmoothTranslate(D3DXVECTOR2(3500 * ratioX, pageButton[1]->GetPosition().y), (j + 3) * eTime);

	return true;
}

bool LobbyScene::OnAlertAnimation(float eTime)
{
	if (animationTime >= 1.5f) return false;

	animationTime += eTime;

	if (isMakeRoom) alert->SmoothTranslate(D3DXVECTOR2(600 * ratioX, 350 * ratioY), 5 * eTime);
	else if (!isMakeRoom) alert->SmoothTranslate(D3DXVECTOR2(600 * ratioX, -500 * ratioY), 5 * eTime);

	return true;
}