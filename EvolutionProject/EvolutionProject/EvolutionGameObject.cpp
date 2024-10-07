#include "EvolutionGameObject.h"
#include "EvolutionCore.h"
#include "EvolutionCamera.h"
#include "EvolutionMath.h"

EVGameObject::EVGameObject() 
{
	_tag = "";

	_parent = NULL;

	_update = true;

	D3DXMatrixIdentity(&_transformMatrix);
	D3DXQuaternionIdentity(&_quaternionAngle);

	_scale			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	_scalingCenter	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotationCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_position		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_eulerAngle		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	_forward		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	_right			= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up				= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

EVGameObject::~EVGameObject()
{
	for (list<EVGameObject*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}

	_child.clear();
}

void EVGameObject::Update()
{
	for (list<EVGameObject*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		if ((*it)->_update)
		{
			(*it)->Update();
		}
	}
}

void EVGameObject::CalcDirectionVector()
{
	_right = EVMath::TransformDirection(&_quaternionAngle, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	_up = EVMath::TransformDirection(&_quaternionAngle, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	_forward = EVMath::TransformDirection(&_quaternionAngle, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void EVGameObject::Render(D3DXMATRIX* combinedMatrix)
{

	D3DXMatrixTransformation(
		&_transformMatrix,
		&_scalingCenter,
		NULL,
		&_scale,
		&_rotationCenter,
		&_quaternionAngle,
		&_position);

	if (combinedMatrix != NULL) 
	{
		_transformMatrix = _transformMatrix * (*combinedMatrix);
	}

	if (_parent != NULL)
	{
		_transformMatrix = _transformMatrix * _parent->_transformMatrix;
	}

	EVSystem->DirectDevice()->SetTransform(D3DTS_WORLD, &_transformMatrix);
}

void EVGameObject::Translate(D3DXVECTOR3 vector)
{
	_position += vector;
}

bool EVGameObject::SmoothRotate(D3DXVECTOR3 target, float speedMultiple)
{
	_eulerAngle = target;

	D3DXQUATERNION targetQuaternion;

	D3DXQuaternionIdentity(&targetQuaternion);

	D3DXQuaternionRotationYawPitchRoll(&targetQuaternion, 
		(float)D3DXToRadian(target.y), 
		(float)D3DXToRadian(target.x), 
		(float)D3DXToRadian(target.z));

	if (_quaternionAngle == targetQuaternion)
	{
		return false;
	}

	D3DXQuaternionSlerp(&_quaternionAngle, &_quaternionAngle, &targetQuaternion, EVTime->DeltaTime() * speedMultiple);

	CalcDirectionVector();

	return true;
}

bool EVGameObject::SmoothTranslate(D3DXVECTOR3 target, float speedMultiple)
{
	if (_position == target)
	{
		return false;
	}

	D3DXVec3Lerp(&_position, &_position, &target, EVTime->DeltaTime() * speedMultiple);

	return true;
}

void EVGameObject::RotateLocalRight(float degree)
{
	_eulerAngle.x += degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &_right, D3DXToRadian(degree));
	_quaternionAngle *= rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotateLocalUp(float degree)
{
	_eulerAngle.y += degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &_up, D3DXToRadian(degree));
	_quaternionAngle *= rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotateLocalForward (float degree)
{
	_eulerAngle.z += degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &_forward, D3DXToRadian(degree));
	_quaternionAngle *= rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotateWorldRight(float degree)
{
	_eulerAngle.x += degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXToRadian(degree));
	_quaternionAngle *= rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotateWorldUp(float degree)
{
	_eulerAngle.y += degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(degree));
	_quaternionAngle *= rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotateWorldForward(float degree)
{
	_eulerAngle.z += degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXToRadian(degree));
	_quaternionAngle *= rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotationUp(float degree)
{
	_eulerAngle.y = degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &_up, D3DXToRadian(degree));
	_quaternionAngle = rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotationRight(float degree)
{
	_eulerAngle.x = degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &_right, D3DXToRadian(degree));
	_quaternionAngle = rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::RotationForward(float degree)
{
	_eulerAngle.z = degree;

	D3DXQUATERNION rot;

	CalcDirectionVector();

	D3DXQuaternionRotationAxis(&rot, &_forward, D3DXToRadian(degree));
	_quaternionAngle = rot;

	D3DXQuaternionNormalize(&_quaternionAngle, &_quaternionAngle);
}

void EVGameObject::PushChildObject(EVGameObject* gameObject, std::string tag, bool isUpdate)
{
	gameObject->_update = isUpdate;
	gameObject->_parent = this;

	gameObject->_tag = tag;

	_child.push_back(gameObject);
}

void EVGameObject::PopChildObject(std::string tag, bool isErase)
{
	for (list<EVGameObject*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		if ((*it)->_tag == tag)
		{
			(*it)->_parent = NULL;
			it = _child.erase(it);

			if (isErase)
			{
				delete (*it);
				if (it == _child.end())
				{
					break;
				}
			}
		}
	}
}

EVGameObject* EVGameObject::FindChildObject(std::string tag)
{
	for (list<EVGameObject*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		if (tag == (*it)->_tag)
		{
			return (*it);
		}
	}

	return NULL;
}