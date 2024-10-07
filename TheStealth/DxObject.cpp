#include "DxObject.h"
#include "DirectX9.h"

DxObject::DxObject()
{
	parent = 0;

	update = true;
	remove = false;
	isExist = true;

	D3DXMatrixIdentity(&worldMatrix);
	D3DXQuaternionIdentity(&quaternionAngle);

	scale			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	scalingCenter	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotationCenter	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	eulerAngle		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	forward			= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	right			= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	up				= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

DxObject::~DxObject()
{
	for (list<DxObject*>::iterator it = child.begin(); it != child.end(); ++it)
	{
		delete (*it);
		(*it) = 0;
	}

	child.clear();
}

void DxObject::Update(float eTime)
{
	for (list<DxObject*>::iterator it = child.begin(); it != child.end(); ++it)
	{
		if ((*it)->update)	
			(*it)->Update(eTime);

		if (!(*it)->remove) 
			continue;

		delete (*it);
		it = child.erase(it);
		if (it == child.end())
			break;
	}
}

D3DXVECTOR3 DxObject::TransformDirection(D3DXQUATERNION* orientation, D3DXVECTOR3* direction)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, orientation);

	D3DXVECTOR3 newDirection;
	newDirection.x = direction->x * rotation._11 + direction->y * rotation._21 + direction->z * rotation._31 + rotation._41;
	newDirection.y = direction->x * rotation._12 + direction->y * rotation._22 + direction->z * rotation._32 + rotation._42;
	newDirection.z = direction->x * rotation._13 + direction->y * rotation._23 + direction->z * rotation._33 + rotation._43;

	memcpy(direction, &newDirection, sizeof(newDirection));

	return *direction;
}

void DxObject::CalcDirectionVector()
{
	right =		TransformDirection(&quaternionAngle, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	up =		TransformDirection(&quaternionAngle, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	forward =	TransformDirection(&quaternionAngle, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void DxObject::Render()
{

	D3DXMatrixTransformation(
		&worldMatrix,
		&scalingCenter,
		0,
		&scale,
		&rotationCenter,
		&quaternionAngle,
		&position);

	if (parent != 0)
	{
		worldMatrix = worldMatrix * parent->worldMatrix;
	}

	DirectX9->GetDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
}

void DxObject::Translate(D3DXVECTOR3 vector)
{
	position += vector;
}

void DxObject::Translate(D3DXVECTOR3 target, float speed, float eTime)
{
	if (position == target) return;

	D3DXVECTOR3 moveDir = target - position;
	float integral = speed / (abs(moveDir.x) + abs(moveDir.y) + abs(moveDir.z));
	position += moveDir * eTime * integral;
}

void DxObject::Rotate(D3DXQUATERNION target, float speed)
{
	if (quaternionAngle == target) return;

	quaternionAngle += target / speed;
	D3DXQuaternionNormalize(&quaternionAngle, &quaternionAngle);

	CalcDirectionVector();
}


void DxObject::SmoothRotate(D3DXQUATERNION target, float speedMultiple)
{

	if (quaternionAngle == target)
		return;

	D3DXQuaternionSlerp(&quaternionAngle, &quaternionAngle, &target, speedMultiple);
	D3DXQuaternionNormalize(&quaternionAngle, &quaternionAngle);

	CalcDirectionVector();
}

void DxObject::SmoothTranslate(D3DXVECTOR3 target, float speedMultiple)
{
	if (position == target) return;

	D3DXVec3Lerp(&position, &position, &target, speedMultiple);
}

void DxObject::MoveLocalZ(float distance)
{
	CalcDirectionVector();
	position += forward * distance;
}

void DxObject::RotateLocalX(float degree)
{
	eulerAngle.x += degree;

	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, &right, D3DXToRadian(degree));
	quaternionAngle *= rot;

	D3DXQuaternionNormalize(&quaternionAngle, &quaternionAngle);

	CalcDirectionVector();
}

void DxObject::RotateLocalY(float degree)
{
	eulerAngle.y += degree;

	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, &up, D3DXToRadian(degree));
	quaternionAngle *= rot;

	D3DXQuaternionNormalize(&quaternionAngle, &quaternionAngle);

	CalcDirectionVector();
}

void DxObject::RotateLocalZ(float degree)
{
	eulerAngle.z += degree;

	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, &forward, D3DXToRadian(degree));
	quaternionAngle *= rot;

	D3DXQuaternionNormalize(&quaternionAngle, &quaternionAngle);

	CalcDirectionVector();
}

float DxObject::Distance(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	D3DXVECTOR3 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void DxObject::AddChild(DxObject* object, bool isUpdate)
{
	object->update = isUpdate;
	object->parent = this;

	child.push_back(object);
}

void DxObject::RemoveChild(DxObject* object)
{
	object->remove = true;
}

void DxObject::SetWorldMatrix(D3DXMATRIX worldMatrix)
{
	this->worldMatrix = worldMatrix;
}
void DxObject::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}
void DxObject::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
void DxObject::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}
void DxObject::SetScalingCenter(float x, float y, float z)
{
	scalingCenter.x = x;
	scalingCenter.y = y;
	scalingCenter.z = z;
}
void DxObject::SetRotationCenter(float x, float y, float z)
{
	rotationCenter.x = x;
	rotationCenter.y = y;
	rotationCenter.z = z;
}
void DxObject::SetRotation(float w, float x, float y, float z)
{
	quaternionAngle.w = w;
	quaternionAngle.x = x;
	quaternionAngle.y = y;
	quaternionAngle.z = z;
}
void DxObject::SetRotation(D3DXQUATERNION rot)
{
	quaternionAngle = rot;
}