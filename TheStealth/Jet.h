#ifndef _JET_H_
#define _JET_H_

#include "Camera.h"
#include "Model.h"
#include "ImageAnimation.h"
#include "Trail.h"
#include "Listener.h"
#include "Server\UDP_Structure.h"

class Camera;

class Jet : public DxObject
{
public :
	Jet(Camera* camera, int team);
	~Jet();

	virtual void Update(float eTime);
	virtual void Render();

	virtual void UpdatePosition(float eTime);

	void ProcessDamage(float damage);

	USER_MOVE_TO_DATA info;

	D3DXVECTOR3 nextPosition;

	bool isDead;

protected :

	int team;
	float accel;
	bool boom;

	Camera* camera;

	Model* model;

	Listener* listener;

	ImageAnimation* fire;
	Trail* trail;

	ImageAnimation* explosion;

	D3DXQUATERNION quat1;
	D3DXQUATERNION quat2;
};

#endif