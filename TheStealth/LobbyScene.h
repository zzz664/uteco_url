#ifndef _LOBBYSCENE_H_
#define _LOBBYSCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Skybox.h"
#include "MyJet.h"
#include "Font.h"
#include "Button.h"
#include "RoomButton.h"
#include "MakeRoomAlert.h"
#include "Water.h"
#include <vector>

using namespace std;

class LobbyScene : public Scene
{

public:

	struct ROOM_INFO
	{
		int id;
		wstring title;
		int currentPerson;
		int maxPerson;
		int state;
	};

private:

	Camera*			camera;
	Skybox*			skybox;

	MyJet*			jet;

	Water*			water;

	Font*			font;

	Sprite*			icon[4];
	Button*			button[4];
	Button*			pageButton[2];

	RoomButton*		roomButton[7];

	MakeRoomAlert*	alert;

	vector<ROOM_INFO> roomInfo;

	int				page;
	int				maxPage;
	
	float			ratioX;
	float			ratioY;

	float			animationTime;

	bool			isInLobby;
	bool			isMakeRoom;
	int				isChangeScene;
	int				roomId;

public:

	LobbyScene();
	~LobbyScene();

	void Update(float eTime);
	void Render();

private:

	void UpdateLobby();
	void UpdateButton(float eTime);
	void UpdateJet(float eTime);

	bool OnLobbyInAnimation(float eTime);
	bool OnLobbyOutAnimation(float eTime);

	bool OnAlertAnimation(float eTime);

	bool OnLoadAnimation(float eTime);
};

#endif