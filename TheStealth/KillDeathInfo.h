#ifndef _KILLDEATHINFO_H_
#define _KILLDEATHINFO_H_

#include "Sprite.h"
#include "Font.h"

class KillDeathInfo : public DxObject2D
{

private:

	Font* kd;
	Font* nickname;
	Sprite* form;
	

	float ratioX;
	float ratioY;

public:

	KillDeathInfo();
	~KillDeathInfo();

	void SetData(int k, int d);

	void Update(float eTime);
	void Render();

	int kill, death;
};

#endif