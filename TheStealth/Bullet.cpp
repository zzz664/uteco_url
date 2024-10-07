#include "Bullet.h"
#include "DirectX9.h"
#include "Time.h"

Bullet::Bullet(Camera* camera, DxObject* origin)
{
	createdTime = TIME->CurrentTime();
	isDelete = false;
	image = new Image(camera, "Resource/Bullet/Bullet.png");
	image->SetBillboardState(BILLBOARD_NONE);
	AddChild(image);
	this->origin = origin;
	position = origin->GetPosition();
	position.x += (rand() % 100) / 300.0f;
	position.x -= (rand() % 100) / 300.0f;
	position.y += (rand() % 100) / 300.0f;
	position.y -= (rand() % 100) / 300.0f;
	quaternionAngle = origin->GetRotation();
	eulerAngle = origin->GetEulerRotation();
	SetScale(0.02f, 0.3f, 1.0f);
}

Bullet::Bullet(const Bullet& other)
{
	isDelete = false;
	createdTime = TIME->CurrentTime();
	image = new Image(*other.image);
	AddChild(image);
	origin = other.origin;
	position = origin->GetPosition();
	position.x += (rand() % 100) / 300.0f;
	position.x -= (rand() % 100) / 300.0f;
	position.y += (rand() % 100) / 300.0f;
	position.y -= (rand() % 100) / 300.0f;
	quaternionAngle = origin->GetRotation();
	eulerAngle = origin->GetEulerRotation();
	SetScale(0.02f, 0.3f, 1.0f);
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	isDelete = false;
	createdTime = TIME->CurrentTime();
	position = origin->GetPosition();
	position.x += (rand() % 100) / 700.0f;
	position.x -= (rand() % 100) / 700.0f;
	position.y += (rand() % 100) / 700.0f;
	position.y -= (rand() % 100) / 700.0f;
	quaternionAngle = origin->GetRotation();
	eulerAngle = origin->GetEulerRotation();

}
void Bullet::Update(float eTime)
{
	DxObject::Update(eTime);
	MoveLocalZ(450.0f * eTime);
	if (TIME->CurrentTime() - createdTime >= 3.0f)
		isDelete = true;
}

void Bullet::Render()
{
	DxObject::Render();
	image->Render();
}