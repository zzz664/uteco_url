#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "Model.h"
#include "Trail.h"
#include "ImageAnimation.h"
#include "Jet.h"

class Missile : public DxObject
{

private:

	Model*			missile;
	Trail*			trail;
	ImageAnimation* fire;


	D3DXVECTOR3		dir;

public:

	Missile(Camera* camera, Jet* target);
	Missile(const Missile& other);
	~Missile();

	void Update(float eTime);
	void Render();


	Jet*		target;
	bool hit;
};

#endif