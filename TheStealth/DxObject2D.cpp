#include "DxObject2D.h"

DxObject2D::DxObject2D()
{
	parent = 0;

	update = true;

	D3DXMatrixIdentity(&worldMatrix);

	scale			= D3DXVECTOR2(1.0f, 1.0f);
	scalingCenter	= D3DXVECTOR2(0.0f, 0.0f);
	rotationCenter	= D3DXVECTOR2(0.0f, 0.0f);
	position		= D3DXVECTOR2(0.0f, 0.0f);
	rotation		= 0.0f;
}

DxObject2D::~DxObject2D()
{
	for (list<DxObject2D*>::iterator it = child.begin(); it != child.end(); ++it)
	{
		delete (*it);
		(*it) = 0;
	}

	child.clear();
}

void DxObject2D::Update(float eTime)
{
	for (list<DxObject2D*>::iterator it = child.begin(); it != child.end(); ++it)
	{
		if ((*it)->update) (*it)->Update(eTime);
	}
}

void DxObject2D::Render()
{
	D3DXMatrixTransformation2D(
		&worldMatrix,
		&scalingCenter,
		0,
		&scale,
		&rotationCenter,
		rotation,
		&position);

	if (parent != 0)
	{
		worldMatrix = worldMatrix * parent->worldMatrix;
	}
}

void DxObject2D::AddChild(DxObject2D* object, bool isUpdate)
{
	object->update = isUpdate;
	object->parent = this;

	child.push_back(object);
}

void DxObject2D::SmoothTranslate(D3DXVECTOR2 target, float speedMultiple)
{
	if (position == target) return;

	D3DXVec2Lerp(&position, &position, &target, speedMultiple);
}

void DxObject2D::SmoothScale(D3DXVECTOR2 target, float speedMultiple)
{
	if (scale == target) return;

	D3DXVec2Lerp(&scale, &scale, &target, speedMultiple);
}

void DxObject2D::SetWorldMatrix(D3DXMATRIX worldMatrix)
{
	this->worldMatrix = worldMatrix;
}

void DxObject2D::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
}

void DxObject2D::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void DxObject2D::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void DxObject2D::SetScalingCenter(float x, float y)
{
	scalingCenter.x = x;
	scalingCenter.y = y;
}

void DxObject2D::SetRotationCenter(float x, float y)
{
	rotationCenter.x = x;
	rotationCenter.y = y;
}