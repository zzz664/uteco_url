#ifndef _ROOMSCENE_H_
#define _ROOMSCENE_H_

#include "Scene.h"
#include "Button.h"
#include "Slot.h"
#include "TextBox.h"
#include "ChatForm.h"

class RoomScene : public Scene
{

private:

	Sprite*		background[4];

	Slot*		slot[8];

	Button*		button[2];

	TextBox*	textBox;
	ChatForm*	chatForm;

	Font*		font;

	string		title;

	float		ratioX;
	float		ratioY;

	float		animationTime;

	bool		isHost;
	int			roomId;

	int			isChangeScene;


	bool		toggleChat;

public:

	RoomScene(int roomId, bool isHost);
	~RoomScene();

	void StartGame();
	void Update(float eTime);
	void Render();

	void ResetSlot(int index);

	ChatForm* GetChatForm() { return chatForm; }
	Slot*	GetSlot(int index) { return slot[index]; }

	void SetTitle(string title) { this->title = title; }

private:

	void UpdateButton();
	void UpdateChat(float eTime);

	bool OnLoadAnimation(float eTime);
	bool OnChangeAnimation(float eTime);

	void SetIndex();

	bool isGetInfo;
};

#endif