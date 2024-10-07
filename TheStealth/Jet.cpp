#include "Jet.h"
#include "SoundManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "../libs/DXUT/Core/DXUT.h"
#include "Server\ServerManager.h"

Jet::Jet(Camera* camera, int team)
{
	this->camera = camera;

	model = new Model(camera, "Resource/FA_22/FA-22.x", "Resource/FA_22/FA-22.png");
	AddChild(model);

	listener = new Listener();

	{
		trail = new Trail(60, 0.08f);

		fire = new ImageAnimation(camera, "Resource/Particles/Fire/", 25, 20.0f);

		fire->SetScale(1.0f, 2.0f, 0.0f);

		fire->RotateLocalZ(45);
		fire->RotateLocalX(90);

		quat1 = fire->GetRotation();

		fire->RotateLocalY(90);
		quat2 = fire->GetRotation();

		AddChild(fire);
		AddChild(trail);
	}

	explosion = new ImageAnimation(camera, "Resource/Particles/Explosion/", 89, 30.0f);
	explosion->SetScale(20.0f, 20.0f, 0.0f);
	AddChild(explosion);

	info.BOOSTTIME = 0.0f;
	info.HP = 100.0f;

	accel = 0.0f;

	isDead = false;

	isExist = false;

	boom = false;

	SOUND->PlayIs(SOUND->JET);
	SOUND->SetVolume(SOUND->JET, 1.0f);
}

Jet::~Jet()
{
	delete listener;
}

void Jet::Update(float eTime)
{
	DxObject::Update(eTime);

	if (isDead == false)
	{
		listener->Update(eTime);

		listener->SetForward(forward);
		listener->SetUp(up);
		listener->SetPosition(camera->GetPosition());

		SOUND->SetSoundPosition(SOUND->JET, position.x, position.y, position.z);

		SOUND->SoundLoop(SOUND->JET, 21.0f, 30.0f);

		fire->SetScale(1.0f, 2.0f + info.BOOSTTIME, 0.0f);
		fire->SetProceed(true);
		
		boom = false;
	}
	else
	{
		if (!boom)
		{
			explosion->SetProceed(true);
		}

		if (explosion->isComplete)
		{
			explosion->SetProceed(false);
			explosion->isComplete = false;
			boom = true;
		}
	}
}

void Jet::Render()
{
	DxObject::Render();
	model->Render();

	fire->SetPosition(0.6f, -0.5f, -6.0f);
	fire->SetRotation(quat1);
	fire->Render();
	fire->SetRotation(quat2);
	fire->Render();

	fire->SetPosition(-0.6f, -0.5f, -6.0f);
	fire->SetRotation(quat1);
	fire->Render();
	fire->SetRotation(quat2);
	fire->Render();

	trail->SetPosition(right * -6.9f + up * -0.85 + forward * -0.75f);
	trail->Render();

	trail->SetPosition(right * 6.9f + up * -0.85 + forward * -0.75f);
	trail->Render();
}

void Jet::UpdatePosition(float eTime)
{
	static float time = 0.0f;
	Rotate(D3DXQUATERNION(info.DX, info.DY, info.DZ, info.DW), 7.5f);
	MoveLocalZ(info.SPEED * eTime);
	time += eTime;
	nextPosition = D3DXVECTOR3(info.X, info.Y, info.Z);

	if (time >= 1.0f)
	{
		if (DxObject::Distance(position, nextPosition) >= 1.0f)
		{
			Translate(nextPosition, 80.0f, eTime);
		}
		if (DxObject::Distance(position, nextPosition) < 1.0f)
		{
			time = 0.0f;
		}
	}
}

void Jet::ProcessDamage(float damage)
{
	BYTE WriteBuffer[MAX_BUFFER_LENGTH] = { 0, };
	// 서버에 패킷 전송
	ServerManager::getInstance().userIocp->mUdpSession.WriteToPacket(
		DEFAULT_ADDRESS,
		DEFAULT_PORT,
		PU_U2C_DAMAGE,
		WriteBuffer,
		WRITE_PU_U2C_DAMAGE(
		WriteBuffer,
		ServerManager::getInstance().Oid,
		info.Oid,
		damage));
}