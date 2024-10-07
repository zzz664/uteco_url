#include "ChatForm.h"
#include "DirectX9.h"

ChatForm::ChatForm(string path, float size)
{
	for (int i = 0; i < 6; ++i) chatLog[i] = "";

	chatForm = new Sprite(path);
	AddChild(chatForm, false);

	font = new Font("KoPubµ¸¿òÃ¼ Medium", 1, size);
	AddChild(font, false);

	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();
}

ChatForm::~ChatForm()
{

}

void ChatForm::Update(float eTime)
{
	DxObject2D::Update(eTime);
}

void ChatForm::Render()
{
	DxObject2D::Render();

	chatForm->Render();

	for (int i = 0; i < 6; ++i)
	{
		font->SetPosition(60 * ratioX, (i * 34 + 28) * ratioY);
		font->SetText("%s", chatLog[5 - i].c_str());
		font->Render();
	}
}

void ChatForm::SetChatLog(string log)
{
	for (int i = 5; i >= 1; --i)
	{
		chatLog[i] = chatLog[i - 1];
	}

	chatLog[0] = log;
}