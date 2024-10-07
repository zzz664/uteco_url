#include "Font.h"
#include "DirectX9.h"

Font::Font(string family, int type, int size)
{
	this->size = size;
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (type == 0)
	{
		D3DXCreateFontA(
			DirectX9->GetDevice(),
			size, size / 2 - size / 10,
			FW_LIGHT,
			D3DX_DEFAULT,
			NULL,
			DEFAULT_CHARSET,
			NULL,
			ANTIALIASED_QUALITY,
			NULL, family.c_str(), &font);
	}

	else if (type == 1)
	{
		D3DXCreateFontA(
			DirectX9->GetDevice(),
			size, size / 2 - size / 10,
			FW_MEDIUM,
			D3DX_DEFAULT,
			NULL,
			DEFAULT_CHARSET,
			NULL,
			ANTIALIASED_QUALITY,
			NULL, family.c_str(), &font);
	}

	else if (type == 2)
	{
		D3DXCreateFontA(
			DirectX9->GetDevice(),
			size, size / 2 - size / 10,
			FW_BOLD,
			D3DX_DEFAULT,
			NULL,
			DEFAULT_CHARSET,
			NULL,
			ANTIALIASED_QUALITY,
			NULL, family.c_str(), &font);
	}

	else
	{
		D3DXCreateFontA(
			DirectX9->GetDevice(),
			size, size / 2 - size / 10,
			FW_LIGHT,
			D3DX_DEFAULT,
			NULL,
			DEFAULT_CHARSET,
			NULL,
			ANTIALIASED_QUALITY,
			NULL, family.c_str(), &font);
	}
}

Font::~Font()
{
	font->Release();
}

void Font::Update(float eTime)
{
	DxObject2D::Update(eTime);
}

void Font::Render()
{
	DxObject2D::Render();

	DirectX9->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	DirectX9->GetSprite()->SetTransform(&worldMatrix);

	font->DrawTextA(DirectX9->GetSprite(), text, -1, NULL, DT_TOP | DT_LEFT, color);

	DirectX9->GetSprite()->End();
}

void Font::SetText(LPCSTR fmt, ...)
{
	char	buff[1024] = { 0, };

	vsprintf(buff, fmt, (char*)(&fmt + 1));

	strcpy(text, buff);
}