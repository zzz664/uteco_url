#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

#include "Bullet.h"
#include "Jet.h"
#include "Sprite.h"
#include <list>

#define MAX_BULLET 180

class BulletManager
{
public:
	BulletManager(Camera* camera, DxObject* origin, Jet** players);
	~BulletManager();

	void Update(float eTime);
	void Render();

private:
	void MakeBullet();

	bool enable;
	bool controlEnable;

	int bulletNum;
	int ratePerSec;
	float accumulatedTime;

	Camera* camera;
	DxObject* origin;

	Jet* players[8];

	list<Bullet*> bulletList;
	Bullet* bullet;

	Sprite*		bulletAim;
};

#endif