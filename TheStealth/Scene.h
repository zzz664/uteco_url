#ifndef _SCENE_H_
#define _SCENE_H_

#include "DxObject.h"
#include "DxObject2D.h"

class Scene
{
protected:

	list<DxObject*>		objects;
	list<DxObject2D*>	objects2D;

public:

	Scene();
	virtual ~Scene();

	virtual void Update(float eTime);
	virtual void Render() = 0;
	
	void AddObject(DxObject* object, bool isUpdate = true);
	void AddObject2D(DxObject2D* object, bool isUpdate = true);

};

#endif