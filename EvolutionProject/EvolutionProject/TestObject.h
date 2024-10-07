#ifndef _TESTOBJECT_H_
#define _TESTOBJECT_H_

#include "EvolutionShape.h"
#include "EvolutionSphereCollider.h"

class TestObject : public EVSphereCollider
{

private:

	EVShape* s;
	EVSphereCollider* c;

public:

	TestObject();
	~TestObject();

	void Update();
	void Render(D3DXMATRIX* combinedMatrix = NULL);

public:

	EVSphereCollider* Collider() { return c; }
};

#endif