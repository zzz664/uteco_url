#include "MakeRoomAlert.h"
#include "DirectX9.h"

MakeRoomAlert::MakeRoomAlert()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	alert = new Sprite("Resource/Lobby/button.png");
	alert->SetScale(3.3f * ratioX, 1.2f * ratioY);
	AddChild(alert, false);

	font = new Font("KoPubµ¸¿òÃ¼ Bold", 2, 50.0f);
	font->SetPosition(175 * ratioX, 25 * ratioY);
	font->SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	font->SetText("M   A   K   E      R   O   O   M");
	AddChild(font, false);

	textBox = new TextBox(0, "Resource/Nickname/nickname_blank.png", 35.0f);
	textBox->Initialize("", 15, false);

	textBox->SetScale(1.8f, 1.0f);
	textBox->SetPosition(58 * ratioX, 100 * ratioY);

	textBox->SetTextBoxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	AddChild(textBox);

	{
		for (int i = 0; i < 2; ++i) button[i] = new Button();

		button[0]->Initialize("Resource/Login/button_1.png", NULL, L"CANCLE", 20.0f);
		button[1]->Initialize("Resource/Login/button_2.png", NULL, L"OK", 20.0f);

		button[0]->SetPosition(165 * ratioX, 230 * ratioY);
		button[1]->SetPosition(385 * ratioX, 230 * ratioY);

		for (int i = 0; i < 2; ++i) AddChild(button[i]);
	}
}

MakeRoomAlert::~MakeRoomAlert()
{

}

void MakeRoomAlert::Update(float eTime)
{
	DxObject2D::Update(eTime);

	textBox->SetFocus(true);
	textBox->Write();
}

void MakeRoomAlert::Render()
{
	DxObject2D::Render();
	alert->Render();
	textBox->Render();
	for (int i = 0; i < 2; ++i) button[i]->Render();
	font->Render();
}