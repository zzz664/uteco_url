#include "Label.h"

Label::Label(string normal, D3DXCOLOR color1, string point, D3DXCOLOR color2, float size)
{
	this->normal = normal;
	this->point = point;

	this->size = size;

	normalColor = color1;
	pointColor = color2;

	font = new Font("KoPubµ¸¿òÃ¼ Bold", 2, size);
	AddChild(font, false);
}

Label::~Label()
{
}

void Label::Update(float eTime)
{

}

void Label::Render()
{
	DxObject2D::Render();

	font->SetPosition(0.0f, 0.0f);

	font->SetText("%s", normal.c_str());

	font->SetColor(normalColor);

	font->Render();

	font->SetPosition((size / 2 - size / 10) * strlen(normal.c_str()), 0.0f);

	font->SetText("%s", point.c_str());

	font->SetColor(pointColor);

	font->Render();
}

void Label::SetNormalColor(D3DXCOLOR color)
{
	normalColor = color;
}

void Label::SetPointColor(D3DXCOLOR color)
{
	pointColor = color;
}