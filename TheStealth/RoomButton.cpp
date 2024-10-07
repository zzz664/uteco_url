#include "RoomButton.h"
#include "DirectX9.h"

RoomButton::RoomButton()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	font = new Font("KoPub돋움체 Bold", 2, 25.0f);

	button = new Button();
	button->Initialize("Resource/Lobby/button.png", "Resource/Lobby/button_select.png", L"", 0.0f);

	button->SetScale(5.0f, 0.3f);

	icon = new Sprite("Resource/Lobby/person_icon.png");
	icon->SetPosition(button->GetArea().right * button->GetScale().x - (350 * ratioX), (30 * ratioY));

	AddChild(font, false);
	AddChild(button);
	AddChild(icon, false);

	id = 0;
	title = "";
	currentPerson = 0;
	maxPerson = 0;
	state = 0;
}

RoomButton::~RoomButton()
{

}

void RoomButton::SetRoom(int id, string title, int currentPerson, int maxPerson, int state)
{
	this->id = id;
	this->title = title;
	this->currentPerson = currentPerson;
	this->maxPerson = maxPerson;
	this->state = state;
}

void RoomButton::Update(float eTime)
{
	DxObject2D::Update(eTime);
}

void RoomButton::Render()
{
	DxObject2D::Render();

	button->Render();

	if (id != 0) icon->Render();

	if (id == 0) return;

	font->SetPosition(30 * ratioX, 30 * ratioY);
	font->SetText("%d", id);
	font->Render();

	font->SetPosition(200 * ratioX, 30 * ratioY);
	font->SetText("%s", title.c_str());
	font->Render();

	font->SetPosition(icon->GetPosition().x + (60 * ratioX), 30 * ratioY);
	font->SetText("%d / %d", currentPerson, maxPerson);
	font->Render();

	font->SetPosition(icon->GetPosition().x + (250 * ratioX), 30 * ratioY);
	if (state == 0)
		font->SetText("%s", "대기중");
	else
		font->SetText("%s", "게임중");
	font->Render();
}