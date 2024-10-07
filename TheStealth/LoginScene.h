#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_

#include "Scene.h"
#include "Button.h"
#include "TextBox.h"
#include "Font.h"
#include "Camera.h"
#include "Skybox.h"
#include "Water.h"

class LoginScene : public Scene
{
private:

	Camera*		camera;
	Skybox*		skybox;
	Water*		water;

	Sprite*		background[2];

	Font*		font;

	Sprite*		logo;
	Sprite*		logo2;
	Sprite*		fade;

	TextBox*	textBox[3];
	Button*		button[3];

	float		ratioX;
	float		ratioY;

	float		animationTime;

	RECT		rect;

	int			id;

	bool		isRegister;
	bool		isCheck;
	bool		isAnimation;
	bool		isTab;
	bool		isLogo;
	int			isChangeScene;

public:

	LoginScene();
	~LoginScene();

	void Update(float eTime);
	void Render();

private:

	void UpdateTextBox();
	void UpdateButton();

	void OnMouseUpdate();
	
	bool OnLogoAnimation(float eTime);
	bool OnLoadAnimation(float eTime);
	bool OnChangeAnimation(float eTime);
	bool OnAnimation(float eTime);
};

#endif