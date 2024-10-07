#include "EvolutionUIFont.h"
#include "EvolutionCore.h"

EVUIFont::EVUIFont(int size)
{
	_text = "";
	_size = size;
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXCreateFontA(
		EVSystem->DirectDevice(),
		size, size / 2 - size / 10,
		FW_HEAVY,
		D3DX_DEFAULT,
		NULL,
		DEFAULT_CHARSET,
		NULL,
		ANTIALIASED_QUALITY,
		NULL, "¸¼Àº°íµñ", &_font);
}

EVUIFont::~EVUIFont()
{
	_font->Release();
}

void EVUIFont::Update()
{
	EVGameObject2D::Update();
}

void EVUIFont::Render()
{
	EVGameObject2D::Render();

	EVSystem->DirectSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	EVSystem->DirectSprite()->SetTransform(&_transformMatrix);

	_font->DrawTextA(EVSystem->DirectSprite(), _text.data(), -1, NULL, DT_TOP | DT_LEFT, _color);

	EVSystem->DirectSprite()->End();
}

void EVUIFont::Text(LPSTR fmt, ...)
{
	char	buff[1024];

	vsprintf(buff, fmt, (char *)(&fmt + 1));

	_text = buff;
}