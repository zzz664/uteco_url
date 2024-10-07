#include "TestObject.h"

TestObject::TestObject()
{
	s = new EVShape("Sphere");
	PushChildObject(s, "sphere", false);

	c = new EVSphereCollider;
	PushChildObject(c, "collider", false);
}

TestObject::~TestObject()
{

}

void TestObject::Update()
{
	EVGameObject::Update();
}

void TestObject::Render(D3DXMATRIX* combinedMatrix)
{
	EVGameObject::Render(combinedMatrix);

	s->Render();
	c->Render();
}