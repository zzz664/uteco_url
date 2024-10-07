#ifndef _KEYBUTTON_H_
#define _KEYBUTTON_H_

#include "DxObject2D.h"
#include "Sprite.h"
#include "Font.h"

using namespace std;

class KeyButton : public DxObject2D
{

private:

	Sprite* usual;
	Sprite* mouseOn;

	Font*	font;

	string caption;
	unsigned short value;

	D3DXCOLOR fontColor;

	RECT	area;

	float	size;

	bool	isChangeKey;

public:

	KeyButton(char* file1, char* file2, float size);
	~KeyButton();

	void Initialize(string caption, unsigned short value, bool isChangeKey);

	void Update(float eTime);
	void Render();

	void SetCaption(string caption);

	void SetValue(unsigned short value);
	unsigned short GetValue();

	void SetButtonColor(D3DXCOLOR color);
	void SetFontColor(D3DXCOLOR color);

	D3DXCOLOR GetButtonColor() { return usual->GetColor(); }
	D3DXCOLOR GetFontColor() { return fontColor; }

	RECT GetArea();

	bool MouseOn();
	bool MouseClick();
};

#endif