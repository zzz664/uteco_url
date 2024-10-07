#ifndef _MISSILEMANAGER_H_
#define _MISSILEMANAGER_H_

#include "Missile.h"
#include "Jet.h"
#include "Sprite.h"
#include <list>

class MissileManager
{
public:
	MissileManager(Camera* camera, DxObject* origin, Jet** players);
	~MissileManager();

	void Update(float eTime);
	void Render();

private :
	void MakeMissile();

	bool heatSeeking;
	bool lockOn;

	float seekingTime;

	bool leftEnable;
	bool rightEnable;

	bool enable;
	bool controlEnable;

	float leftTime;
	float rightTime;

	Camera* camera;
	DxObject* origin;

	Jet* players[8];

	Jet* target;

	Missile* missile;
	list<Missile*> missileList;

	ImageAnimation* leftExplosion;
	ImageAnimation* rightExplosion;

	Sprite* seekSight;
	Sprite* lockOnSight;
	Sprite* missileAim;
};

#endif