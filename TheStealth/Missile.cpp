#include "Missile.h"
#include "Camera.h"
#include "InputManager.h"

Missile::Missile(Camera* camera, Jet* target)
{
	this->target = target;

	missile = new Model(camera, "Resource/Missile/missile.x", "Resource/Missile/missile.png");

	trail = new Trail(60, 0.2f);
	trail->SetPosition(-0.04f, 0.0f, 0.0f);

	fire = new ImageAnimation(camera, "Resource/Particles/Fire/", 25, 20.0f);
	fire->SetPosition(-0.04f, 0.01f, -5.0f);
	fire->SetScale(0.4f, 4.5f, 0.0f);
	fire->RotateLocalX(-90);

	AddChild(missile);
	AddChild(trail);
	AddChild(fire);

	isExist = true;
	hit = false;
}

Missile::Missile(const Missile& other)
{
	target = NULL;
	missile = NULL;
	trail = NULL;
	fire = NULL;
	target = other.target;
	missile = other.missile;
	trail = other.trail;
	trail->SetPosition(-0.04f, 0.0f, 0.0f);
	fire = other.fire;
	fire->SetPosition(-0.04f, 0.01f, -5.0f);
	fire->SetScale(0.4f, 4.5f, 0.0f);
	fire->RotateLocalX(-90);

	AddChild(missile);
	AddChild(trail);
	AddChild(fire);

	isExist = true;
	hit = false;
}

Missile::~Missile()
{

}

void Missile::Update(float eTime)
{
	DxObject::Update(eTime);

	D3DXVec3Normalize(&dir, &(target->GetPosition() - position));

	Translate(dir * 500 * eTime);

	if (DxObject::Distance(target->GetPosition(), position) <= 5.0f) { isExist = false; hit = true; }
}

void Missile::Render()
{
	DxObject::Render();
	missile->Render();
	fire->Render();
	trail->Render();
}