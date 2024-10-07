#ifndef _OTHERBULLETMANAGER_H_
#define _OTHERBULLETMANAGER_H_

#include "Bullet.h"
#include "Jet.h"
#include <list>

#ifndef MAX_BULLET
#define MAX_BULLET 180
#endif

class OtherBulletManager
{
public:
	OtherBulletManager(Camera* camera, Jet** origins);
	~OtherBulletManager();

	void Update(float eTime);
	void Render();

private:
	void MakeBullet(int index);

	int bulletNum[8];

	Camera* camera;
	Jet** origins;

	list<Bullet*> bulletList;
	Bullet* bullet[8];
};

#endif