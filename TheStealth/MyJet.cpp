#include "MyJet.h"
#include "InputManager.h"
#include "SceneManager.h"

MyJet::MyJet(Camera* camera) : Jet(camera, 0)
{
	info.SPEED = 0.0f;

	isEngineStart = false;
	spawnTime = 0.0f;
}

MyJet::~MyJet()
{
}

void MyJet::Initialize(float basicSpeed, float minSpeed, float maxSpeed)
{
	this->basicSpeed = basicSpeed;
	this->maxSpeed = maxSpeed;
	this->minSpeed = minSpeed;

	info.SPEED = basicSpeed;
}

void MyJet::Update(float eTime)
{
	isDead = !info.IsAlive;

	if (isDead == FALSE)
	{
		Jet::Update(eTime);
		UpdateSpeed(eTime);
		UpdateMove(eTime);
	}
	
	else
	{
		spawnTime += eTime;
		if (spawnTime >= 5.0f)
		{
			// ¸®½ºÆù
			spawn = true;
			spawnTime = 0.0f;
		}
	}
}


void MyJet::Render()
{
	if (isDead == false)
	{
		Jet::Render();
	}
}


void MyJet::UpdateMove(float eTime)
{
	if (INPUT->GetKey(VK_UP))
		{
			RotateLocalX(90 * eTime);
		}

		if (INPUT->GetKey(VK_DOWN))
		{
			RotateLocalX(-90 * eTime);
		}

		if (INPUT->GetKey(VK_LEFT))
		{
			RotateLocalZ(135 * eTime);
		}

		if (INPUT->GetKey(VK_RIGHT))
		{
			RotateLocalZ(-135 * eTime);
		}

		if (INPUT->GetKey('A'))
		{
			RotateLocalY(-10 * eTime);
		}

		if (INPUT->GetKey('D'))
		{
			RotateLocalY(10 * eTime);
		}

		MoveLocalZ(info.SPEED * eTime);

		//if (SceneManager->currentSceneNum == INGAME)
		//{
		//	UpdatePosition(eTime);
		//}
	
}


void MyJet::UpdateSpeed(float eTime)
{
	if (isEngineStart)
	{
		accel += 3 * eTime;
		info.SPEED += accel * eTime;

		if (info.SPEED >= basicSpeed)
		{
			info.SPEED = basicSpeed;
			accel = 0.0f;
			isEngineStart = false;
		}
	}

	if (!isEngineStart)
	{
		if (INPUT->GetKey('W'))
		{
			accel += 10 * eTime;
		}
		else if (INPUT->GetKey('S'))
		{
			accel -= 10 * eTime;
			info.SPEED -= 30 * eTime;
			info.BOOSTTIME = -1.0f;
		}
		accel -= 3 * eTime;

		if (INPUT->GetKey(VK_LSHIFT))
		{
			info.BOOSTTIME += eTime * 30;
			if (info.BOOSTTIME > 3.0f) { info.BOOSTTIME = 3.0f; }
			accel += 15 * eTime;
			info.SPEED += 10.0f * eTime;
		}
		else
		{
			info.BOOSTTIME -= eTime * 30;
			if (info.BOOSTTIME < 0.0f) { info.BOOSTTIME = 0.0f; }
		}

		if (accel < 0.0f) { accel = 0.0f; }
		else if (accel > 15.0f) { accel = 15.0f; }

		info.SPEED += accel * eTime;

		if (info.SPEED > basicSpeed) { info.SPEED -= eTime; }
		else if (info.SPEED < basicSpeed) { info.SPEED += eTime; }

		if (info.SPEED > maxSpeed) { info.SPEED = maxSpeed; accel = 0.0f; }
		else if (info.SPEED < minSpeed) { info.SPEED = minSpeed; }
	}
}

void MyJet::UpdatePosition(float eTime)
{
	static float time = 0.0f;
	time += eTime;
	nextPosition = D3DXVECTOR3(info.X, info.Y, info.Z);

	if (time >= 1.0f)
	{
		if (DxObject::Distance(position, nextPosition) >= 10.0f)
		{
			Translate(nextPosition, 10.0f, eTime);
		}
		if (DxObject::Distance(position, nextPosition) < 10.0f)
		{
			time = 0.0f;
		}
	}
}