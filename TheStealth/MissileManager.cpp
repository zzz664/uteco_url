#include "MissileManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DirectX9.h"
#include "SoundManager.h"
#include "Server\ServerManager.h"
#include "Camera.h"
#include "Def.h"

MissileManager::MissileManager(Camera* camera, DxObject* origin, Jet** players)
{
	missile = new Missile(camera, NULL);

	this->camera = camera;
	this->origin = origin;

	missileList.clear();

	heatSeeking = false;
	lockOn = false;

	leftEnable = true;
	rightEnable = true;

	leftTime = 0.0f;
	rightTime = 0.0f;

	enable = false;
	controlEnable = true;

	for (int i = 0; i < 8; ++i)
	{
		this->players[i] = players[i];
	}

	target = NULL;

	seekSight = new Sprite("Resource/Aim/Seeking.png");
	lockOnSight = new Sprite("Resource/Aim/LockOn.png");

	missileAim = new Sprite("Resource/Aim/MissileAim.png");
	missileAim->SetPosition(910 * DirectX9->GetRatioX(), 500 * DirectX9->GetRatioY());

	leftExplosion = new ImageAnimation(camera, "Resource/Particles/Explosion/", 89, 30.0f);
	leftExplosion->SetScale(10.0f, 10.0f, 0.0f);

	rightExplosion = new ImageAnimation(camera, "Resource/Particles/Explosion/", 89, 30.0f);
	rightExplosion->SetScale(10.0f, 10.0f, 0.0f);
}

MissileManager::~MissileManager()
{
	for (list<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	missileList.clear();
	delete missile;
}

void MissileManager::Update(float eTime)
{
	if (INPUT->GetKeyDown(VK_RETURN) && SceneManager->currentSceneNum == INGAME) { controlEnable = !controlEnable; }
	if (enable)
	{
		if (leftEnable == false)
		{
			leftTime += eTime;
			if (leftTime >= 10.0f)
			{
				leftEnable = true;
				leftTime = 0.0f;
			}
		}

		if (rightEnable == false)
		{
			rightTime += eTime;
			if (rightTime >= 10.0f)
			{
				rightEnable = true;
				rightTime = 0.0f;
			}
		}

		heatSeeking = false;
		D3DXVECTOR3 dir;
		for (int i = 0; i < 8; ++i)
		{
			if (players[i]->info.Oid != 1) { continue; printf("Continue\n"); }
			dir = origin->GetPosition() - players[i]->GetPosition();
			CLog::WriteLog(L"Dir XYZ : %.2lf %.2lf %.2lf\n", dir.x, dir.y, dir.z);

			D3DXMATRIX mat;
			D3DXMatrixRotationQuaternion(&mat, &origin->GetRotation());
			D3DXVec3TransformCoord(&dir, &dir, &mat);
			CLog::WriteLog(L"Dir XYZ : %.2lf %.2lf %.2lf\n", dir.x, dir.y, dir.z);

			float dot = D3DXVec3Dot(&origin->GetPosition(), &players[i]->GetPosition());
			float scale = D3DXVec3Length(&origin->GetPosition()) * D3DXVec3Length(&players[i]->GetPosition());
			float cos = dot / scale;

			if (dir.z < 0.0f && DxObject::Distance(origin->GetPosition(), players[i]->GetPosition()) <= 1000.0f && cos < D3DXToRadian(60.0f))
			{
				heatSeeking = true;

				if (target != NULL)
				{
					if (DxObject::Distance(origin->GetPosition(), target->GetPosition()) > DxObject::Distance(origin->GetPosition(), players[i]->GetPosition()))
					{
						target = players[i];
					}
				}
				else
				{
					target = players[i];
				}

			}
		}

		if (heatSeeking)
		{
			D3DXVECTOR2 v = Convert3Dto2D(camera, target->GetPosition());

			lockOnSight->SetPosition(v.x - 15, v.y - 15);
			seekSight->SetPosition(v.x - 15, v.y - 15);

			seekingTime += eTime;
			if (seekingTime >= 3.0f)
			{
				lockOn = true;
				seekingTime = 3.0f;
				SOUND->Stop(SOUND->HEATSEEKING);
				SOUND->PlayIs(SOUND->LOCKON);
			}
			else
			{
				lockOn = false;
				SOUND->Stop(SOUND->LOCKON);
				SOUND->PlayIs(SOUND->HEATSEEKING);
			}
		}
		else
		{
			lockOn = false;
			SOUND->Stop(SOUND->LOCKON);
			SOUND->Stop(SOUND->HEATSEEKING);
			seekingTime -= eTime * 3;
			if (seekingTime < 0.0f)
			{
				seekingTime = 0.0f;
			}
		}
	}
	if (controlEnable)
	{
		if (INPUT->GetKey('1'))
		{
			lockOn = false;
			heatSeeking = false;
			seekingTime = 0.0f;
			SOUND->Stop(SOUND->LOCKON);
			SOUND->Stop(SOUND->HEATSEEKING);
			enable = false;
		}
		else if (INPUT->GetKey('2')) { enable = true; }

		if (INPUT->GetKeyDown(VK_SPACE) && enable && lockOn && (leftEnable || rightEnable))
		{
			MakeMissile();
		}
	}

	for (list<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
	{
		if (missileList.empty()) { return; CLog::WriteLog(L"Missile List is empty"); }
		if ((*it)->isExist)
		{
			(*it)->Update(eTime);
		}
		else
		{
			(*it)->target->ProcessDamage(45.0f);
			if (leftExplosion->GetProceed() == false)
			{
				leftExplosion->SetProceed(true);
			}
			else if (rightExplosion->GetProceed() == false)
			{
				rightExplosion->SetProceed(true);
			}

			if (leftExplosion->GetProceed())
			{
				leftExplosion->Update(eTime);
				leftExplosion->SetPosition((*it)->GetPosition());
				CLog::WriteLog(L"Left boom, %.2lf %.2lf %.2lf", leftExplosion->GetPosition().x, leftExplosion->GetPosition().y, leftExplosion->GetPosition().z);
			}
			else if (rightExplosion->GetProceed())
			{
				rightExplosion->Update(eTime);
				rightExplosion->SetPosition((*it)->GetPosition());
				CLog::WriteLog(L"Right boom, %.2lf %.2lf %.2lf", rightExplosion->GetPosition().x, rightExplosion->GetPosition().y, rightExplosion->GetPosition().z);
			}
			it = missileList.erase(it);
			return;
		}

		if (leftExplosion->isComplete)
		{
			leftExplosion->SetProceed(false);
			leftExplosion->isComplete = false;
		}

		if (rightExplosion->isComplete)
		{
			rightExplosion->SetProceed(false);
			rightExplosion->isComplete = false;
		}
	}
}

void MissileManager::Render()
{
	for (list<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
	{
		(*it)->Render();
	}

	if (enable)
	{
		missileAim->Render();
	}

	if (leftExplosion->GetProceed())
	{
		leftExplosion->Render();
	}

	if (rightExplosion->GetProceed())
	{
		rightExplosion->Render();
	}

	if (heatSeeking)
	{
		if (lockOn)
		{
			lockOnSight->Render();
		}
		else
		{
			seekSight->Render();
		}
	}
}

void MissileManager::MakeMissile()
{
	missileList.push_back(new Missile(*missile));
	missileList.back()->target = target;
	missileList.back()->SetRotation(origin->GetRotation());

	if (leftEnable)
	{
		missileList.back()->SetPosition(origin->GetPosition() + origin->GetRight() * -3);
		leftEnable = false;
	}
	else if (rightEnable)
	{
		missileList.back()->SetPosition(origin->GetPosition() + origin->GetRight() * 3);
		rightEnable = false;
	}
}