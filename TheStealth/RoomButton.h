#ifndef _ROOMBUTTON_H_
#define _ROOMBUTTON_H_

#include "DxObject2D.h"
#include "Button.h"
#include "Font.h"
#include <string>

using namespace std;

class RoomButton : public DxObject2D
{

private:

	Button* button;
	Sprite* icon;

	Font*	font;

	int		id;
	string	title;
	int		currentPerson;
	int		maxPerson;
	int		state;
	
	float	ratioX;
	float	ratioY;

public:

	RoomButton();
	~RoomButton();

	void SetRoom(int id, string title, int currentPerson, int maxPerson, int state);

	int GetId() { return id; }

	bool MouseClick() { return button->MouseClick(); }
	bool MouseOn() { return button->MouseOn(); }

	void Update(float eTime);
	void Render();
};

#endif