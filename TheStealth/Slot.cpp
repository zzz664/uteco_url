#include "Slot.h"
#include "DirectX9.h"

Slot::Slot(int id, bool isHost)
{
	this->id = id;
	this->isHost = isHost;

	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	font = new Font("KoPubµ¸¿òÃ¼ Bold", 1, 25.0f);
	AddChild(font, false);

	if ((id + 1) < 5)
	{
		image1 = new Sprite("Resource/Room/name_blank.png");
		image2 = new Sprite("Resource/Room/leader_blank.png");

		font->SetPosition(80 * ratioX, 16 * ratioY);
	}

	else if ((id + 1) > 4)
	{
		image1 = new Sprite("Resource/Room/name_blank2.png");
		image2 = new Sprite("Resource/Room/leader_blank2.png");

		font->SetPosition(115 * ratioX, 16 * ratioY);
	}

	AddChild(image1, false);
	AddChild(image2, false);

	font->SetText("");

	memset(caption, 0, BUFSIZ);
}

Slot::~Slot()
{

}

void Slot::Update(float eTime)
{
	DxObject2D::Update(eTime);
}

void Slot::Render()
{
	DxObject2D::Render();
	
	if (isHost) image2->Render();
	else image1->Render();
	
	font->Render();
}

void Slot::SetSlotCaption(const char* caption)
{
	strcpy(this->caption, caption);

	memcpy(this->caption, caption, sizeof(char) * strlen(caption));

	font->SetText("%s", this->caption);
}