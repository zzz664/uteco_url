#ifndef _FONT_H_
#define _FONT_H_

#include "DxObject2D.h"
#include <string>

using namespace std;

class Font : public DxObject2D
{
private:

	LPD3DXFONT	font;
	D3DXCOLOR	color;

	char		text[BUFSIZ];
	int			size;

public:

	Font(string family, int type, int size);
	~Font();

	void Update(float eTime);
	void Render();

public:

	void SetText(LPCSTR fmt, ...);
	void SetColor(D3DXCOLOR color) { this->color = color; }
};

#endif