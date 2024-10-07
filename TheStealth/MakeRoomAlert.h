#ifndef _MAKEROOMALERT_H_
#define _MAKEROOMALERT_H_

#include "DxObject2D.h"
#include "TextBox.h"
#include "Font.h"
#include "Button.h"

class MakeRoomAlert : public DxObject2D
{

private:

	Sprite*		alert;
	Font*		font;
	TextBox*	textBox;
	Button*		button[2];

	float		ratioX;
	float		ratioY;

public:

	MakeRoomAlert();
	~MakeRoomAlert();

	void Update(float eTime);
	void Render();

	void Reset() { textBox->Reset(""); }

	WCHAR* GetText() { return textBox->GetStringBuffer_UNICODE(); }

	bool GetCancleClick() { return button[0]->MouseClick(); }
	bool GetOKClick() { return button[1]->MouseClick(); }

};

#endif