#ifndef _CHATFORM_H_
#define _CHATFORM_H_

#include "DxObject2D.h"
#include "Sprite.h"
#include "Font.h"
#include <string>

using namespace std;

class ChatForm : public DxObject2D
{
	
private:

	Sprite*		chatForm;
	Font*		font;

	string		chatLog[6];

	float		ratioX;
	float		ratioY;

public:

	ChatForm(string path, float size);
	~ChatForm();

	void Update(float eTime);
	void Render();

	void SetChatLog(string log);
};

#endif