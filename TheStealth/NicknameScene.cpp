#include "NicknameScene.h"
#include "LobbyScene.h"
#include "Automata.h"
#include "KeyTable.h"
#include "SceneManager.h"
#include "Server\ServerManager.h"

NicknameScene::NicknameScene()
{
	animationTime = 0.0f;

	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	AUTOMATA->SetEnableHangul(false);
	AUTOMATA->SetEnable(false);
	AUTOMATA->ClearBuffer();

	isAlert = false;
	isChangeScene = false;

	{
		camera = new Camera();
		camera->MoveTo(0.0f, 100.0f, 0.0f);

		skybox = new Skybox(camera);
		skybox->Create();

		water = new Water(camera, 100000.0f);

		AddObject(skybox);
		AddObject(water);
	}

	{
		background = new Sprite("Resource/Nickname/background_circle-01.png");

		background->SetPosition(1920 * ratioX, 0.0f);

		AddObject2D(background, false);
	}

	{
		label[0] = new Label("User", D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), "Nickname", D3DXCOLOR(0.8f, 0.5f, 0.0f, 1.0f), 35.0f);
		label[1] = new Label("Input", D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), "option", D3DXCOLOR(0.8f, 0.5f, 0.0f, 1.0f), 35.0f);

		label[0]->SetPosition((1920 + 640) * ratioX, 200 * ratioY);
		label[1]->SetPosition((1920 + 1477) * ratioX, 200 * ratioY);

		for (int i = 0; i < 2; ++i) AddObject2D(label[i], false);
	}

	{
		textBox = new TextBox(0, "Resource/Nickname/nickname_blank.png", 30.0f);
		textBox->Initialize("", 8, false);

		textBox->SetPosition(label[0]->GetPosition().x, 270 * ratioY);

		AddObject2D(textBox);
	}

	{
		changeKey[0] = new KeyButton("Resource/Nickname/change_button.png", "Resource/Nickname/change_button_select.png", 30.0f);
		changeKey[1] = new KeyButton("Resource/Nickname/change_button.png", "Resource/Nickname/change_button_select.png", 30.0f);

		changeKey[0]->SetPosition(label[1]->GetPosition().x, label[1]->GetPosition().y + (70 * ratioY));
		changeKey[1]->SetPosition(label[1]->GetPosition().x + (150 * ratioX), label[1]->GetPosition().y + (70 * ratioY));

		changeKey[0]->Initialize("ÇÑ±Û", NULL, true);
		changeKey[1]->Initialize("ENG", NULL, true);


		for (int i = 0; i < 2; ++i) AddObject2D(changeKey[i]);

		string tmp;
		int index = 0;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (KeyTable::englishTable[i][j] == NULL) continue;

				else
				{
					keyButton[index] = new KeyButton("Resource/Nickname/keyboard_button.png", "Resource/Nickname/keyboard_button_select.png", 20.0f);

					tmp = KeyTable::englishTable[i][j];
					keyButton[index]->Initialize(tmp, KeyTable::englishTable[i][j], false);
				}

				if (i == 1) keyButton[index]->SetPosition((126 * j + 630) * ratioX, (123 * i + 400) * ratioY);

				else keyButton[index]->SetPosition((126 * j + 600) * ratioX, (123 * i + 400) * ratioY);

				keyButton[index]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				keyButton[index]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

				AddObject2D(keyButton[index]);

				index++;
			}
		}

		del = new KeyButton("Resource/Nickname/keyboard_button.png", "Resource/Nickname/keyboard_button_select.png", 20.0f);
		del->Initialize("DEL", 8, false);

		del->SetPosition(keyButton[25]->GetPosition().x + (126 * ratioX), keyButton[25]->GetPosition().y);
		del->SetScale(1.35f, 1.0f);

		del->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		del->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		AddObject2D(del);


		enter = new KeyButton("Resource/Nickname/keyboard_button.png", "Resource/Nickname/keyboard_button_select.png", 20.0f);
		enter->Initialize("ENTER", 13, false);

		enter->SetPosition(del->GetPosition().x + (156 * ratioX), del->GetPosition().y);
		enter->SetScale(2.0f, 1.0f);

		enter->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		enter->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		AddObject2D(enter);
	}
}

NicknameScene::~NicknameScene()
{
	delete camera;
}

void NicknameScene::Update(float eTime)
{
	Scene::Update(eTime);

	if (!OnLoadAnimation(eTime))
	{
		UpdateTextBox();
		UpdateButton();

		if (isChangeScene)
		{
			if (OnChangeAnimation(eTime) == false)
			{
				SceneManager->ChangeScene(new LobbyScene);
				return;
			}
		}
	}
}

void NicknameScene::Render()
{
	skybox->Render();
	water->Render();

	background->Render();

	textBox->Render();

	for (int i = 0; i < 2; ++i) label[i]->Render();

	for (int i = 0; i < 2; ++i) changeKey[i]->Render();

	for (int i = 0; i < 26; ++i) keyButton[i]->Render();

	enter->Render();

	del->Render();
}

void NicknameScene::UpdateButton()
{
	if (changeKey[0]->MouseClick())
	{
		if (AUTOMATA->GetIsEnglish())
		{
			int index = 0;
			std::string tmp;

			AUTOMATA->SetIsEnglish(false);

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (KeyTable::koreanTable[i][j] == "") 
						continue;

					else
					{
						tmp = KeyTable::koreanTable[i][j];
						keyButton[index]->SetCaption(tmp);
					}
					index++;
				}
			}
		}
	}

	if (changeKey[1]->MouseClick())
	{
		if (!AUTOMATA->GetIsEnglish())
		{
			int index = 0;
			std::string tmp;

			AUTOMATA->SetIsEnglish(true);

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (KeyTable::englishTable[i][j] == NULL)
						continue;

					else
					{
						tmp = KeyTable::englishTable[i][j];
						keyButton[index]->SetCaption(tmp);
					}
					index++;
				}
			}
		}
	}

	for (int i = 0; i < 26; ++i)
	{
		if (keyButton[i]->MouseClick())
		{
			if (isAlert)
			{
				isAlert = false;
			}
			AUTOMATA->KeyPush(keyButton[i]->GetValue());
		}
	}

	if (del->MouseClick())
	{
		if (isAlert)
		{
			isAlert = false;
		}
		AUTOMATA->KeyPush(del->GetValue());
	}

	if (enter->MouseClick())
	{
		if (strlen(textBox->GetStringBuffer()) < 5)
		{
			isAlert = true;
			return;
		}

		else
		{
			if (ServerManager::getInstance().QueryNickName(textBox->GetStringBuffer_UNICODE()))
			{
				if (ServerManager::getInstance().InsertNickName(textBox->GetStringBuffer_UNICODE()))
				{
				}

				isChangeScene = true;
				animationTime = 0.0f;
				return;
			}

			else
			{
				isAlert = true;
				textBox->Reset("");
				return;
			}
		}
	}
}

void NicknameScene::UpdateTextBox()
{
	textBox->SetFocus(true);
	textBox->Write();

	if (isAlert)
	{
		textBox->SetTextBoxColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
	}

	else
	{
		textBox->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

bool NicknameScene::OnLoadAnimation(float eTime)
{
	static float accelation = 0.0f;

	if (accelation>= 1.0f)
	{
		return false;
	}

	animationTime += eTime;

	background->SmoothTranslate(D3DXVECTOR2(0.0f, 0.0f), 3 * eTime);

	label[0]->SmoothTranslate(D3DXVECTOR2(640 * ratioX, 200 * ratioY), 3 * eTime);
	label[1]->SmoothTranslate(D3DXVECTOR2(1477 * ratioX, 200 * ratioY), 3 * eTime);

	textBox->SmoothTranslate(D3DXVECTOR2(640 * ratioX, 270 * ratioY), 3 * eTime);

	changeKey[0]->SmoothTranslate(D3DXVECTOR2(1477 * ratioX, 270 * ratioY), 3 * eTime);
	changeKey[1]->SmoothTranslate(D3DXVECTOR2((1477 + 150) * ratioX, 270 * ratioY), 3 * eTime);

	if (animationTime > 2.5f)
	{
		accelation += 3 * eTime;

		for (int i = 0; i < 26; ++i)
		{
			keyButton[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
			keyButton[i]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
		}

		del->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
		del->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));

		enter->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
		enter->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
	}

	return true;
}

bool NicknameScene::OnChangeAnimation(float eTime)
{
	static float accelation = 1.0f;

	if (animationTime >= 2.5f)
	{
		return false;
	}

	accelation -= 3 * eTime;

	enter->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
	enter->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));

	del->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
	del->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));

	for (int i = 25; i >= 0; --i)
	{
		keyButton[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
		keyButton[i]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, accelation));
	}

	if (accelation<= 0.0f)
	{
		animationTime += eTime;
	
		background->SmoothTranslate(D3DXVECTOR2(1920 * ratioX, 0.0f), 3 * eTime);

		label[0]->SmoothTranslate(D3DXVECTOR2((1920 + 640) * ratioX, 200 * ratioY), 3 * eTime);
		label[1]->SmoothTranslate(D3DXVECTOR2((1920 + 1477) * ratioX, 200 * ratioY), 3 * eTime);

		textBox->SmoothTranslate(D3DXVECTOR2((1920 + 640) * ratioX, 270 * ratioY), 3 * eTime);

		changeKey[0]->SmoothTranslate(D3DXVECTOR2((1920 + 1477) * ratioX, 270 * ratioY), 3 * eTime);
		changeKey[1]->SmoothTranslate(D3DXVECTOR2((1920 + 1477 + 150) * ratioX, 270 * ratioY), 3 * eTime);
	}


	return true;
}