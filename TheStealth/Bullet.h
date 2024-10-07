#ifndef _BULLET_H_
#define _BULLET_H_

#include "Camera.h"
#include "Image.h"

class Bullet : public DxObject
{
public:
	Bullet(Camera* camera, DxObject* origin);
	Bullet(const Bullet& other);
	~Bullet();

	void Init();
	void Update(float eTime);
	void Render();
	bool isDelete;

private:
	float createdTime;

	void MoveBullet(float eTime);

	Image* image;
	DxObject* origin;

	char owner[32];
};

#endif