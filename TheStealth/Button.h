#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "DxObject2D.h"
#include "Font.h"
#include "Sprite.h"

class Button : public DxObject2D
{
private:

	Sprite* usual;
	Sprite* mouseOn;

	Font*	font;

	LPCWSTR	caption;

	D3DXCOLOR fontColor;

	RECT	area;

	float	size;

public:

	Button();
	~Button();

	void Initialize(char* file1, char* file2, LPCWSTR caption, float size);

	void Update(float eTime);
	void Render();

	void SetCaption(LPCWSTR caption);

	void SetButtonColor(D3DXCOLOR color);
	void SetFontColor(D3DXCOLOR color);

	D3DXCOLOR GetButtonColor() { return usual->GetColor(); }
	D3DXCOLOR GetFontColor() { return fontColor; }

	LPCWSTR GetCaption();
	RECT	GetArea();

	bool MouseOn();
	bool MouseClick();


};

#endif