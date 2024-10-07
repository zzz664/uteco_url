#include "KeyButton.h"
#include "InputManager.h"
#include "Automata.h"

KeyButton::KeyButton(char* file1, char* file2, float size)
{
	font = new Font("KoPubµ¸¿òÃ¼ Bold", 2, size);

	usual = new Sprite(file1);
	AddChild(usual, false);

	if (mouseOn != NULL)
	{
		mouseOn = new Sprite(file2);
		mouseOn->SetPosition(
			-(mouseOn->GetWidth() - usual->GetWidth()) / 2,
			-(mouseOn->GetHeight() - usual->GetHeight()) / 2);
		AddChild(mouseOn, false);
	}

	else
	{
		mouseOn = NULL;
	}

	this->size = size;

	area.left = GetPosition().x;
	area.top = GetPosition().y;
	area.right = area.left + usual->GetWidth();
	area.bottom = area.top + usual->GetHeight();
}

KeyButton::~KeyButton()
{
	delete font;
}

void KeyButton::Initialize(string caption, unsigned short value, bool isChangeKey)
{
	this->caption = caption;
	this->value = value;
	this->isChangeKey = isChangeKey;

	font->SetText("%s", this->caption.c_str());
}

void KeyButton::Update(float eTime)
{
	area.left = GetPosition().x;
	area.top = GetPosition().y;
	area.right = area.left + usual->GetWidth() * scale.x;
	area.bottom = area.top + usual->GetHeight() * scale.y;
}

void KeyButton::Render()
{
	DxObject2D::Render();

	usual->Render();

	if (MouseOn() && mouseOn != NULL)
	{
		mouseOn->Render();
	}

	if (isChangeKey)
	{
		font->SetPosition(
			GetPosition().x + usual->GetWidth() / 2 - (size / 2 - size / 10) / 2 * strlen(caption.c_str()),
			GetPosition().y + (usual->GetHeight() - size) / 2);
	}

	else if (!isChangeKey)
	{
		font->SetPosition(
			GetPosition().x + usual->GetWidth() / 2 - (size / 2 - size / 10) / 2 * strlen(caption.c_str()),
			GetPosition().y + (usual->GetHeight() - size) / 2);
	}

	font->Render();
}

void KeyButton::SetValue(unsigned short value)
{
	this->value = value;
}

unsigned short KeyButton::GetValue()
{
	if (!isChangeKey)
	{
		if (!AUTOMATA->GetIsEnglish() && value != 8)
		{
			return value + 32;
		}

		else
		{
			return value;
		}
	}

	return 0;
}

void KeyButton::SetCaption(string caption)
{
	this->caption = caption;

	font->SetText("%s", caption.c_str());
}

RECT KeyButton::GetArea()
{
	return area;
}

bool KeyButton::MouseOn()
{
	int x, y;

	INPUT->GetMousePosition(x, y);

	if (x >= area.left && x <= area.right &&
		y >= area.top && y <= area.bottom)
	{
		return true;
	}

	return false;
}

bool KeyButton::MouseClick()
{
	if (MouseOn())
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			return true;
		}
	}

	return false;
}

void KeyButton::SetButtonColor(D3DXCOLOR color)
{
	usual->SetColor(color);

	if (mouseOn != NULL)
	{
		mouseOn->SetColor(color);
	}
}

void KeyButton::SetFontColor(D3DXCOLOR color)
{
	fontColor = color;
	font->SetColor(color);
}