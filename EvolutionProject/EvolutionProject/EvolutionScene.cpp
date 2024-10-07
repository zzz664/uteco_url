#include "EvolutionScene.h"

EVScene::EVScene()
{

}

EVScene::~EVScene()
{
	for (list<EVGameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}

	_gameObjects.clear();

	for (list<EVGameObject2D*>::iterator it = _gameObjects2D.begin(); it != _gameObjects2D.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}

	_gameObjects2D.clear();
}

void EVScene::Update()
{
	for (list<EVGameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
	{
		if ((*it)->IsUpdate())
		{
			(*it)->Update();
		}
	}

	for (list<EVGameObject2D*>::iterator it = _gameObjects2D.begin(); it != _gameObjects2D.end(); ++it)
	{
		if ((*it)->IsUpdate())
		{
			(*it)->Update();
		}
	}
}

void EVScene::PushGameObject(EVGameObject* gameObject, std::string tag, bool isUpdate)
{
	gameObject->Tag(tag);
	gameObject->SetUpdate(isUpdate);

	_gameObjects.push_back(gameObject);
}

void EVScene::PushGameObject2D(EVGameObject2D* gameObject, std::string tag, bool isUpdate)
{
	gameObject->Tag(tag);
	gameObject->SetUpdate(isUpdate);

	_gameObjects2D.push_back(gameObject);
}

void EVScene::PopGameObject(std::string tag, bool isErase)
{
	for (list<EVGameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
	{
		if (tag == (*it)->Tag())
		{
			it = _gameObjects.erase(it);

			if (isErase)
			{
				delete (*it);
				if (it == _gameObjects.end())
				{
					break;
				}
			}
		}
	}
}

void EVScene::PopGameObject2D(std::string tag, bool isErase)
{
	for (list<EVGameObject2D*>::iterator it = _gameObjects2D.begin(); it != _gameObjects2D.end(); ++it)
	{
		if ((*it)->Tag() == tag)
		{
			it = _gameObjects2D.erase(it);

			if (isErase)
			{
				delete (*it);
				if (it == _gameObjects2D.end())
				{
					break;
				}
			}
		}
	}
}

EVGameObject* EVScene::FindGameObject(std::string tag)
{
	for (list<EVGameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
	{
		if (tag == (*it)->Tag())
		{
			return (*it);
		}
	}

	return NULL;
}

EVGameObject* EVScene::FindChildObject(EVGameObject* gameObject, std::string tag)
{
	return gameObject->FindChildObject(tag);
}

EVGameObject2D* EVScene::FindGameObject2D(std::string tag)
{
	for (list<EVGameObject2D*>::iterator it = _gameObjects2D.begin(); it != _gameObjects2D.end(); ++it)
	{
		if (tag == (*it)->Tag())
		{
			return (*it);
		}
	}

	return NULL;
}

EVGameObject2D* EVScene::FindChildObject2D(EVGameObject2D* gameObject, std::string tag)
{
	return gameObject->FindChildObject(tag);
}