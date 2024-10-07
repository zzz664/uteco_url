#include "LoginScene.h"
#include "NicknameScene.h"
#include "LobbyScene.h"
#include "Automata.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Server\ServerManager.h"

LoginScene::LoginScene()
{
	ServerManager::getInstance();
	animationTime = 0.0f;

	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	AUTOMATA->ClearBuffer();
	AUTOMATA->SetEnable(false);
	AUTOMATA->SetEnableHangul(false);

	id = -1;

	isRegister = false;
	isAnimation = false;
	isCheck = false;
	isTab = false;
	isLogo = true;
	isChangeScene = 2;

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
		background[0] = new Sprite("Resource/Login/form.png");
		background[1] = new Sprite("Resource/Login/target.png");

		background[0]->SetPosition(1920 * ratioX, 0.0f);
		background[1]->SetPosition(-1920 * ratioX, 0.0f);

		for (int i = 0; i < 2; ++i) AddObject2D(background[i], false);
	}

	{
		font = new Font("KoPub돋움체 Bold", 2, 30.0f);
		font->SetText("PRESS ENTER TO START...");
		font->SetPosition(860 * ratioX, 700 * ratioY);

		logo = new Sprite("Resource/Etc/logo.png");
		logo2 = new Sprite("Resource/Etc/logo_white.png");
		fade = new Sprite("Resource/Etc/fade.png");

		logo->SetPosition(810 * ratioX, 450 * ratioY);
		logo2->SetPosition(810 * ratioX, 450 * ratioY);

		rect.top = logo->GetRect().top / ratioY;
		rect.left = logo->GetRect().left / ratioX;
		rect.right = 0;
		rect.bottom = logo->GetRect().bottom / ratioY;
		logo2->SetRect(rect);

		AddObject2D(font);
		AddObject2D(logo, false);
		AddObject2D(logo2, false);
		AddObject2D(fade, false);
	}

	{
		textBox[0] = new TextBox(0, "Resource/Login/username_blank.png", 30.0f);
		textBox[1] = new TextBox(1, "Resource/Login/password_blank.png", 30.0f);
		textBox[2] = new TextBox(2, "Resource/Login/confirm_blank.png", 30.0f);

		textBox[0]->Initialize("Username", 16, false);
		textBox[1]->Initialize("Password", 16, true);
		textBox[2]->Initialize("Confirm password", 16, true);

		textBox[0]->SetPosition((1920 + 745) * ratioX, 480 * ratioY);
		textBox[1]->SetPosition((1920 + 745) * ratioX, 560 * ratioY);
		textBox[2]->SetPosition(715 * ratioX, 560 * ratioY);

		textBox[2]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		textBox[2]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		for (int i = 0; i < 3; ++i) AddObject2D(textBox[i]);
	}

	{
		for (int i = 0; i < 3; ++i) button[i] = new Button();

		button[0]->Initialize("Resource/Login/button_1.png", NULL, L"Sign up", 30.0f);
		button[1]->Initialize("Resource/Login/button_2.png", NULL, L"Login", 30.0f);
		button[2]->Initialize("Resource/Login/check_button.png", NULL, L"CHECK", 15.0f);

		button[2]->SetFontColor(D3DCOLOR_ARGB(255, 255, 255, 255));

		button[0]->SetPosition((1920 + 745) * ratioX, 650 * ratioY);
		button[1]->SetPosition((1920 + 955) * ratioX, 650 * ratioY);
		button[2]->SetPosition(1150 * ratioX, 490 * ratioY);
		button[2]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		button[2]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		for (int i = 0; i < 3; ++i) AddObject2D(button[i]);
	}

	SOUND->PlayIs(SOUND->BACKGROUND);
	SOUND->SetVolume(SOUND->BACKGROUND, 0.5f);
}

LoginScene::~LoginScene()
{
	delete camera;
}

void LoginScene::Update(float eTime)
{
	Scene::Update(eTime);

	if (OnLogoAnimation(eTime) == false)
	{
		if (INPUT->GetKeyDown(VK_RETURN) && isLogo == true)
		{
			isLogo = false;
			animationTime = 0.0f;
		}
	}

	if (isLogo == false)
	{
		if (OnLoadAnimation(eTime) == false)
		{
			if (OnAnimation(eTime) == false)
			{
				UpdateTextBox();
				UpdateButton();
			}

			OnMouseUpdate();

			if (isChangeScene == 0)
			{
				if (OnChangeAnimation(eTime) == false)
				{
					SceneManager->ChangeScene(new NicknameScene);
					return;
				}
			}

			else if (isChangeScene == 1)
			{
				if (OnChangeAnimation(eTime) == false)
				{
					SceneManager->ChangeScene(new LobbyScene);
					return;
				}
			}
		}
	}
}

void LoginScene::Render()
{
	skybox->Render();
	water->Render();

	fade->Render();

	if (isLogo)
	{
		logo2->Render();
		font->Render();
	}

	for (int i = 0; i < 2; ++i) background[i]->Render();

	if (isLogo == false)
	{
		logo->Render();

		for (int i = 0; i < 2; ++i) textBox[i]->Render();

		if (isRegister) textBox[2]->Render();

		for (int i = 0; i < 2; ++i) button[i]->Render();

		if (isRegister) button[2]->Render();
	}
}

void LoginScene::UpdateTextBox()
{
	if (!isRegister)
	{
		if (id != -1)
		{
			if (INPUT->GetKeyDown(VK_TAB))
			{
				isTab = false;

				id++;
				if (id > 1)
					id = -1;
			}
		}

		if (textBox[0]->MouseClick() || (id == textBox[0]->GetId() && isTab == false))
		{
			isTab = true;

			id = textBox[0]->GetId();

			AUTOMATA->SetEnable(true);
			AUTOMATA->SetBuffer(textBox[0]->GetStringBuffer());

			textBox[0]->SetFocus(true);

		}

		if (textBox[1]->MouseClick() || (id == textBox[1]->GetId() && isTab == false))
		{
			isTab = true;

			id = textBox[1]->GetId();

			AUTOMATA->SetEnable(true);
			AUTOMATA->SetBuffer(textBox[1]->GetStringBuffer());

			textBox[1]->SetReset(false);
			textBox[1]->SetFocus(true);
		}


		{
			if (!textBox[0]->MouseOn() && !textBox[1]->MouseOn())
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					id = -1;
					AUTOMATA->SetEnable(false);
				}
			}

			if (id != textBox[0]->GetId())
			{
				textBox[0]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				textBox[0]->SetFocus(false);
			}

			if (id != textBox[1]->GetId())
			{
				textBox[1]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				textBox[1]->SetFocus(false);
			}
		}

		{
			if (textBox[0]->GetFocus())
			{
				textBox[0]->Write();
				textBox[0]->SetTextBoxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
				return;
			}

			if (textBox[1]->GetFocus())
			{
				textBox[1]->Write();
				textBox[1]->SetTextBoxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
				return;
			}
		}
	}

	else
	{
		{
			if (id != -1)
			{
				if (INPUT->GetKeyDown(VK_TAB))
				{
					isTab = false;

					id++;
					if (id > 2)
						id = -1;
				}
			}

			if (textBox[0]->MouseClick() || (id == textBox[0]->GetId() && isTab == false))
			{
				isTab = true;

				id = textBox[0]->GetId();

				AUTOMATA->SetEnable(true);
				AUTOMATA->SetBuffer(textBox[0]->GetStringBuffer());

				textBox[0]->SetFocus(true);

				isCheck = false;

				button[2]->SetCaption(L"Check");
				button[2]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			if (textBox[1]->MouseClick() || (id == textBox[1]->GetId() && isTab == false))
			{
				isTab = true;

				id = textBox[1]->GetId();

				AUTOMATA->SetEnable(true);
				AUTOMATA->SetBuffer(textBox[1]->GetStringBuffer());

				textBox[1]->SetReset(false);
				textBox[1]->SetFocus(true);
			}

			if (textBox[2]->MouseClick() || (id == textBox[2]->GetId() && isTab == false))
			{
				isTab = true;

				id = textBox[2]->GetId();

				AUTOMATA->SetEnable(true);
				AUTOMATA->SetBuffer(textBox[2]->GetStringBuffer());

				textBox[2]->SetReset(false);
				textBox[2]->SetFocus(true);
			}
		}

		{
			if (!textBox[0]->MouseOn() && !textBox[1]->MouseOn() && !textBox[2]->MouseOn())
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					id = -1;
					AUTOMATA->SetEnable(false);
				}
			}

			if (id != textBox[0]->GetId())
			{
				textBox[0]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				textBox[0]->SetFocus(false);
			}

			if (id != textBox[1]->GetId())
			{
				textBox[1]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				textBox[1]->SetFocus(false);
			}

			if (id != textBox[2]->GetId())
			{
				textBox[2]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				textBox[2]->SetFocus(false);
			}
		}

		{
			if (textBox[0]->GetFocus())
			{
				textBox[0]->Write();
				textBox[0]->SetTextBoxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
				return;
			}

			if (textBox[1]->GetFocus())
			{
				textBox[1]->Write();
				textBox[1]->SetTextBoxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
				return;
			}

			if (textBox[2]->GetFocus())
			{
				textBox[2]->Write();
				textBox[2]->SetTextBoxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
				return;
			}
		}
	}
}

void LoginScene::UpdateButton()
{
	if (!isRegister)
	{
		if (button[0]->MouseClick())
		{
			textBox[0]->Reset("Username");
			textBox[1]->Reset("Password");
			textBox[2]->Reset("Confirm password");

			button[0]->SetCaption(L"Cancel");
			button[1]->SetCaption(L"Sign up");

			id = -1;
			animationTime = 0.0f;

			isRegister = true;
			isAnimation = true;

			return;
		}

		if (button[1]->MouseClick() || INPUT->GetKeyDown(VK_RETURN))
		{
			if (id != -1)
			{
				isTab = false;
				id = -1;
			}

			if (strlen(textBox[0]->GetStringBuffer()) < 4)
			{
				textBox[0]->Reset("4글자이상 입력해주세요.");
			}

			if (strlen(textBox[1]->GetStringBuffer()) < 6)
			{
				textBox[1]->Reset("6글자이상 입력해주세요.");
				return;
			}


			if (ServerManager::getInstance().Login(textBox[0]->GetStringBuffer_UNICODE(), textBox[1]->GetStringBuffer_UNICODE()))
			{
				if (ServerManager::getInstance().GetNickName())
				{
					isChangeScene = 1;
				}
				else
				{
					isChangeScene = 0;
				}
				return;
			}

			else
			{
				textBox[0]->Reset("로그인 실패, 다시 시도해주세요.");
				textBox[1]->Reset("로그인 실패, 다시 시도해주세요.");
				return;
			}
		}
	}

	else
	{
		if (button[2]->MouseClick())					
		{
			if (strlen(textBox[0]->GetStringBuffer()) < 4)
			{
				textBox[0]->Reset("4글자이상으로 입력해주세요.");
				return;
			}

			char* tmp;
			tmp = textBox[0]->GetStringBuffer();

			for (int i = 0; i < strlen(tmp); ++i)
			{
				if (tmp[i] >= 33 && tmp[i] <= 47
					|| tmp[i] >= 58 && tmp[i] <= 64
					|| tmp[i] >= 91 && tmp[i] <= 96
					|| tmp[i] >= 123 && tmp[i] <= 126)
				{
					textBox[0]->Reset("특수문자를 빼주세요.");
					return;
				}
			}

			if (ServerManager::getInstance().Query(textBox[0]->GetStringBuffer_UNICODE()))
			{
				isCheck = true;
				button[2]->SetCaption(L"OK");

				if (isCheck)
				{
					button[2]->SetButtonColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				}
			}

			else
			{
				textBox[0]->Reset("이미 존재하는 아이디입니다.");
				button[2]->SetCaption(L"NO");
				button[2]->SetButtonColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

		}

		if (button[0]->MouseClick())
		{
			textBox[0]->Reset("Username");
			textBox[1]->Reset("Password");
			textBox[2]->Reset("Confirm password");

			button[0]->SetCaption(L"Sign up");
			button[1]->SetCaption(L"Login");

			id = -1;
			animationTime = 0.0f;

			isRegister = false;
			isAnimation = true;
		}

		if (button[1]->MouseClick() || INPUT->GetKeyDown(VK_RETURN))				
		{
			if (id != -1)
			{
				isTab = false;
				id = -1;
			}

			if (!isCheck)
			{
				textBox[0]->Reset("중복체크를 해주세요.");
				return;
			}

			if (strlen(textBox[0]->GetStringBuffer()) < 4)
			{
				textBox[0]->Reset("4글자이상으로 입력해주세요.");
			}

			if (strlen(textBox[1]->GetStringBuffer()) < 6)
			{
				textBox[1]->Reset("6글자이상으로 입력해주세요.");
				return;
			}

			char* tmp;
			tmp = textBox[0]->GetStringBuffer();

			for (int i = 0; i < strlen(tmp); ++i)
			{
				if (tmp[i] >= 33 && tmp[i] <= 47
					|| tmp[i] >= 58 && tmp[i] <= 64
					|| tmp[i] >= 91 && tmp[i] <= 96
					|| tmp[i] >= 123 && tmp[i] <= 126)
				{
					textBox[0]->Reset("특수문자를 빼주세요.");
				}
			}

			tmp = textBox[1]->GetStringBuffer();

			for (int i = 0; i < strlen(tmp); ++i)
			{
				if (tmp[i] >= 33 && tmp[i] <= 47
					|| tmp[i] >= 58 && tmp[i] <= 64
					|| tmp[i] >= 91 && tmp[i] <= 96
					|| tmp[i] >= 123 && tmp[i] <= 126)
				{
					textBox[1]->Reset("특수문자를 빼주세요.");
				}
			}

			tmp = textBox[2]->GetStringBuffer();

			for (int i = 0; i < strlen(tmp); ++i)
			{
				if (tmp[i] >= 33 && tmp[i] <= 47
					|| tmp[i] >= 58 && tmp[i] <= 64
					|| tmp[i] >= 91 && tmp[i] <= 96
					|| tmp[i] >= 123 && tmp[i] <= 126)
				{
					textBox[2]->Reset("특수문자를 빼주세요.");
					return;
				}
			}

			if (!strcmp(textBox[1]->GetStringBuffer(), textBox[2]->GetStringBuffer()))
			{
			
				if (ServerManager::getInstance().SIGNUP(textBox[0]->GetStringBuffer_UNICODE(), textBox[1]->GetStringBuffer_UNICODE()))
				{
					textBox[0]->Reset("Username");
					textBox[1]->Reset("Password");
					id = -1;
					animationTime = 0.0f;

					isRegister = false;
					isAnimation = true;
					return;
				}

				else
				{
					textBox[0]->Reset("회원가입 실패");
					textBox[1]->Reset("회원가입 실패");
					textBox[2]->Reset("회원가입 실패");
					return;
				}
			}
			else
			{
				textBox[2]->Reset("비밀번호가 틀립니다.");
				return;
			}
		}
	}
}

void LoginScene::OnMouseUpdate()
{
	for (int i = 0; i < 2; ++i) 
	{
		if (button[i]->MouseOn())
		{
			button[i]->SetButtonColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
		}

		else
		{
			button[i]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

bool LoginScene::OnLogoAnimation(float eTime)
{
	if (isLogo == false || animationTime >= 1.5)
	{
		return false;
	}

	else
	{
		animationTime += eTime;

		background[0]->SmoothTranslate(D3DXVECTOR2(0.0f, 0.0f), 5 * eTime);
		background[1]->SmoothTranslate(D3DXVECTOR2(0.0f, 0.0f), 5 * eTime);

		rect.right += 5;
		logo2->SetRect(rect);
	}
}

bool LoginScene::OnLoadAnimation(float eTime)
{
	if (animationTime >= 1.5)
	{
		return false;
	}

	else
	{
		animationTime += eTime;

		fade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fade->GetColor().a - 5 * eTime));

		logo->SmoothTranslate(D3DXVECTOR2(810 * ratioX, 280 * ratioY), 5 * eTime);

		textBox[0]->SmoothTranslate(D3DXVECTOR2(745 * ratioX, 480 * ratioY), 5 * eTime);
		textBox[1]->SmoothTranslate(D3DXVECTOR2(745 * ratioX, 560 * ratioY), 5 * eTime);

		button[0]->SmoothTranslate(D3DXVECTOR2(745 * ratioX, 650 * ratioY), 5 * eTime);
		button[1]->SmoothTranslate(D3DXVECTOR2(955 * ratioX, 650 * ratioY), 5 * eTime);
	}

	return true;
}

bool LoginScene::OnChangeAnimation(float eTime)
{
	static float accelation = 1.0f;

	if (animationTime >= 1.5f)
	{
		return false;
	}

	animationTime += eTime;

	background[0]->SmoothTranslate(D3DXVECTOR2(1920 * ratioX, 0.0f), 5 * eTime);
	background[1]->SmoothTranslate(D3DXVECTOR2(-1920 * ratioX, 0.0f), 5 * eTime);

	textBox[0]->SmoothTranslate(D3DXVECTOR2((1920 * 745) * ratioX, 480 * ratioY), 5 * eTime);
	textBox[1]->SmoothTranslate(D3DXVECTOR2((1920 * 745) * ratioX, 560 * ratioY), 5 * eTime);

	button[0]->SmoothTranslate(D3DXVECTOR2((1920 * 745) * ratioX, 650 * ratioY), 5 * eTime);
	button[1]->SmoothTranslate(D3DXVECTOR2((1920 * 955) * ratioX, 650 * ratioY), 5 * eTime);

	return true;
}

bool LoginScene::OnAnimation(float eTime)
{
	static float accelation = 0.0f;

	if (!isRegister)
	{
		if (accelation <= 0.0f)
		{
			accelation = 0.0f;
			return false;
		}
	}
	
	else
	{
		if (accelation >= 1.0f)
		{
			accelation = 1.0f;
			return false;
		}
	}

	if (!isRegister)
	{
		accelation -= 3 * eTime;

		textBox[0]->SmoothTranslate(D3DXVECTOR2(745 * ratioX, 480.0f * ratioY), 5 * eTime);
		textBox[1]->SmoothTranslate(D3DXVECTOR2(745 * ratioX, 560.0f * ratioY), 5 * eTime);

		textBox[2]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		textBox[2]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		button[2]->SmoothTranslate(D3DXVECTOR2(1170 * ratioX, 490.0f * ratioY), 5 * eTime);
		button[2]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		button[2]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	else
	{
		accelation += eTime;

		textBox[0]->SmoothTranslate(D3DXVECTOR2(715 * ratioX, 400.0f * ratioY), 5 * eTime);
		textBox[1]->SmoothTranslate(D3DXVECTOR2(715 * ratioX, 480.0f * ratioY), 5 * eTime);

		textBox[2]->SetTextBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		textBox[2]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		button[2]->SmoothTranslate(D3DXVECTOR2(1150 * ratioX, 410.0f * ratioY), 5 * eTime);
		button[2]->SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		button[2]->SetFontColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return true;
}