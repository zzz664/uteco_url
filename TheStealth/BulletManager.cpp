#include "BulletManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DirectX9.h"
#include "Server\ServerManager.h"

BulletManager::BulletManager(Camera* camera, DxObject* origin, Jet** players)
{
	bullet = new Bullet(camera, origin);
	this->camera = camera;
	this->origin = origin;
	bulletList.clear();
	bulletNum = 0;
	ratePerSec = 20;
	accumulatedTime = 0.0f;
	enable = true;
	controlEnable = true;

	for (int i = 0; i < 8; ++i)
	{
		this->players[i] = players[i];
	}

	bulletAim = new Sprite("Resource/Aim/BulletAim.png");
	bulletAim->SetPosition(910 * DirectX9->GetRatioX(), 500 * DirectX9->GetRatioY());
}

BulletManager::~BulletManager()
{
	for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	bulletList.clear();
	delete bullet;
}

void BulletManager::Update(float eTime)
{
	accumulatedTime += eTime;
	ServerManager::getInstance().isFired = false;

	if (INPUT->GetKeyDown(VK_RETURN) && SceneManager->currentSceneNum == INGAME) { controlEnable = !controlEnable; }

	if (controlEnable)
	{
		if (INPUT->GetKey('1')) { enable = true; }
		else if (INPUT->GetKey('2')) { enable = false; }

		if (INPUT->GetKey(VK_SPACE) && accumulatedTime * 1000.0f > (1000.0f / ratePerSec) && enable)
		{
			accumulatedTime = 0.0f;
			bulletNum++;
			MakeBullet();
			ServerManager::getInstance().isFired = true;
		}
	}

	for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		if (!(*it)->isDelete)
		{
			(*it)->Update(eTime);

			for (int i = 0; i < 8; ++i)
			{
				if (players[i]->isExist == false) { continue; }
				if (DxObject::Distance((*it)->GetPosition(), players[i]->GetPosition()) <= 5.0f)
				{
					(*it)->isDelete = true;
					players[i]->ProcessDamage(5.0f);
				}
			}
		}
	}
}

void BulletManager::Render()
{
	for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		if (!(*it)->isDelete)
		{
			(*it)->Render();
		}
	}

	if (enable)
	{
		bulletAim->Render();
	}
}

void BulletManager::MakeBullet()
{
	if (bulletNum < MAX_BULLET)
		bulletList.push_back(new Bullet(*bullet));
	else
	{
		for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
		{
			if ((*it)->isDelete)
			{
				(*it)->Init();
				break;
			}
		}
	}
}