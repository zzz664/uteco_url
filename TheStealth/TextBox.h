#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include "DxObject2D.h"
#include "Sprite.h"
#include "Font.h"
#include "DirectX9.h"

class TextBox : public DxObject2D
{

private:

	Sprite*		textBox;
	Font*		font;

	RECT		area;

	float		size;

	string		caption;

	char*		stringBuffer;
	WCHAR*		stringBuffer_unicode;

	D3DXCOLOR	fontColor;

	int			limit;
	int			id;

	bool		isFocus;
	bool		isSecure;
	bool		isReset;

public:

	TextBox(int id, char* file, float size);
	~TextBox();

	void Initialize(string caption, int limit, bool isSecure);
	void Write();

	void Update(float eTime);
	void Render();

public:

	bool MouseClick();
	bool MouseOn();

	void SetTextBoxColor(D3DXCOLOR color);
	void SetFontColor(D3DXCOLOR color);

	D3DXCOLOR GetButtonColor() { return textBox->GetColor(); }
	D3DXCOLOR GetFontColor() { return fontColor; }

	void SetFocus(bool focus);
	bool GetFocus();

	void SetReset(bool reset);
	bool GetReset();

	int GetLimit();
	int GetId();

	char* GetStringBuffer();

	WCHAR* GetStringBuffer_UNICODE();

	void Reset(string caption);

	RECT GetArea() { return area; }
};

#endif