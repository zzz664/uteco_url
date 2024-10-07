#ifndef _SLOT_H_
#define _SLOT_H_

#include "DxObject2D.h"
#include "Sprite.h"
#include "Font.h"

using namespace std;

class Slot : public DxObject2D
{

private:

	Sprite* image1;
	Sprite* image2;

	Font*	font;

	char	caption[BUFSIZ];

	int		id;
	int		userId;

	bool	isHost;

	float	ratioX;
	float	ratioY;

public:

	Slot(int id, bool isHost);
	~Slot();

	void SetSlotCaption(const char* caption);
	char* GetSlotCaption() { return caption; }
	
	void SetUserId(int userId) { this->userId = userId; }
	int GetUserId() { return userId; }

	void SetHost(bool isHost) { this->isHost = isHost; }

	int GetId() { return id; }
	bool GetHost() { return isHost; }

	void Update(float eTime);
	void Render();
};

#endif