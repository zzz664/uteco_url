#ifndef _RAIDER_H_
#define _RAIDER_H_

#include "Sprite.h"
#include "DxObject.h"

class Raider : public DxObject2D
{

public:

	struct RaiderEntity
	{
		Sprite* sprite;
		DxObject* object;
		D3DXVECTOR2 dir;
		bool isVisible;
	};

private:

	Sprite* raider;
	
	RaiderEntity entity[8];
	DxObject* player;

	float ratioX;
	float ratioY;

public:

	Raider(DxObject* player, DxObject* objects[]);
	~Raider();

	void SetTarget(DxObject* objects[]);
	void Update(float eTime);
	void Render();
};

#endif