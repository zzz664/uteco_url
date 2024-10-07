#ifndef _NICKNAMESCENE_H_
#define _NICKNAMESCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Skybox.h"
#include "Water.h"
#include "KeyButton.h"
#include "TextBox.h"
#include "Label.h"

class NicknameScene : public Scene
{

private:

	Camera*		camera;
	Skybox*		skybox;
	Water*		water;

	Sprite*		background;
	
	TextBox*	textBox;

	Label*		label[2];

	KeyButton*	changeKey[2];

	KeyButton*	keyButton[26];
	KeyButton*	enter;
	KeyButton*	del;

	float		ratioX;
	float		ratioY;

	float		animationTime;

	bool		isAlert;
	bool		isChangeScene;

public:

	NicknameScene();
	~NicknameScene();

	void Update(float eTime);
	void Render();

private:

	void UpdateButton();
	void UpdateTextBox();

	bool OnLoadAnimation(float eTime);
	bool OnChangeAnimation(float eTime);
};

#endif