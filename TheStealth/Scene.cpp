#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (list<DxObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		delete (*it);
		(*it) = 0;
	}

	objects.clear();

	for (list<DxObject2D*>::iterator it = objects2D.begin(); it != objects2D.end(); ++it)
	{
		delete (*it);
		(*it) = 0;
	}

	objects2D.clear();
}

void Scene::Update(float eTime)
{
	for (list<DxObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->IsUpdate()) (*it)->Update(eTime);
	}

	for (list<DxObject2D*>::iterator it = objects2D.begin(); it != objects2D.end(); ++it)
	{
		if ((*it)->IsUpdate()) (*it)->Update(eTime);
	}
}

void Scene::AddObject(DxObject* object, bool isUpdate)
{
	object->SetUpdate(isUpdate);

	objects.push_back(object);
}

void Scene::AddObject2D(DxObject2D* object, bool isUpdate)
{
	object->SetUpdate(isUpdate);

	objects2D.push_back(object);
}