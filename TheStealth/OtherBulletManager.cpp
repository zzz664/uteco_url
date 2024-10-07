#include "OtherBulletManager.h"
#include "SceneManager.h"
#include "Server\ServerManager.h"

OtherBulletManager::OtherBulletManager(Camera* camera, Jet** origins)
{
	for (int i = 0; i < 8; ++i)
	{
		bullet[i] = new Bullet(camera, origins[i]);
		bulletNum[i] = 0;
	}

	this->camera = camera;
	this->origins = origins;
	bulletList.clear();
}

OtherBulletManager::~OtherBulletManager()
{
	for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	bulletList.clear();
	delete bullet;
}

void OtherBulletManager::Update(float eTime)
{

	for (int i = 0; i < 8; ++i)
	{
		if (!origins[i]->isExist) { continue; }
		if (origins[i]->info.isFired)
		{
			++bulletNum[i];
			MakeBullet(i);
		}
	}

	for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		if (!(*it)->isDelete)
		{
			(*it)->Update(eTime);
		}
	}
}

void OtherBulletManager::Render()
{
	for (list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		if (!(*it)->isDelete)
		{
			(*it)->Render();
		}
	}
}

void OtherBulletManager::MakeBullet(int index)
{
	if (bulletNum[index] < MAX_BULLET)
		bulletList.push_back(new Bullet(*bullet[index]));
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