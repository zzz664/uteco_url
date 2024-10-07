#include "Button.h"
#include "InputManager.h"

Button::Button()
{
	usual = 0;
	mouseOn = 0;
}

Button::~Button()
{
	delete font;
}

void Button::Initialize(char* file1, char* file2, LPCWSTR caption, float size)
{
	this->caption = caption;

	this->size = size;

	usual = new Sprite(file1);
	AddChild(usual, false);

	if (file2 != NULL)
	{
		mouseOn = new Sprite(file2);
		AddChild(mouseOn, false);
	}

	else
	{
		mouseOn = NULL;
	}

	font = new Font("KoPubµ¸¿òÃ¼ Medium", 1, size);
	font->SetColor(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));

	font->SetText("%ws", caption);

	area.left = GetPosition().x;
	area.top = GetPosition().y;
	area.right = area.left + usual->GetWidth() * scale.x;
	area.bottom = area.top + usual->GetHeight() * scale.y;
}

void Button::Update(float eTime)
{
	float x = 0.0f;
	float y = 0.0f;
	
	if (parent != NULL)
	{
		x = parent->GetPosition().x;
		y = parent->GetPosition().y;
	}

	area.left = GetPosition().x + x;
	area.top = GetPosition().y + y;
	area.right = area.left + usual->GetWidth() * scale.x;
	area.bottom = area.top + usual->GetHeight() * scale.y;
}

void Button::Render()
{
	DxObject2D::Render();

	float x = 0.0f;
	float y = 0.0f;

	if (parent != NULL)
	{
		x = parent->GetPosition().x;
		y = parent->GetPosition().y;
	}

	font->SetPosition(
		x + GetPosition().x + usual->GetWidth() / 2 - (size / 2 - size / 10) / 2 * lstrlenW(caption),
		y + GetPosition().y + (usual->GetHeight() - size) / 2);

	if (MouseOn() && mouseOn != NULL)
		mouseOn->Render();
	else
		usual->Render();

	font->Render();
}

void Button::SetCaption(LPCWSTR caption)
{
	this->caption = caption;

	font->SetText("%ws", caption);
}

bool Button::MouseOn()
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

bool Button::MouseClick()
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

void Button::SetButtonColor(D3DXCOLOR color)
{
	usual->SetColor(color);
}

void Button::SetFontColor(D3DXCOLOR fontColor)
{
	this->fontColor = fontColor;
	font->SetColor(fontColor);
}

LPCWSTR Button::GetCaption()
{
	return caption;
}

RECT Button::GetArea()
{
	return area;
}