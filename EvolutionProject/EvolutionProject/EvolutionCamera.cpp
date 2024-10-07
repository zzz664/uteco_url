#include "EvolutionCamera.h"
#include "EvolutionCore.h"
#include "EvolutionMath.h"

EVCamera::EVCamera()
{
	_position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_look		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	_up			= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXQuaternionIdentity(&_orientation);

	D3DXMatrixIdentity(&_viewMatrix);
	D3DXMatrixIdentity(&_projectionMatrix);
	D3DXMatrixIdentity(&_billboardMatrix);

	_skyBox = NULL;
}

EVCamera::~EVCamera()
{
}

void EVCamera::Initialize(EVSkyBox* skyBox)
{
	_skyBox = skyBox;
	UpdateView();
	UpdateProjection(90, EVSystem->Width() / EVSystem->Height(), 1.0f, 1000.0f);
}

void EVCamera::UpdateView()
{
	_skyBox->Position(_position);

	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, -_position.x, -_position.y, -_position.z);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &D3DXQUATERNION(-_orientation.x, -_orientation.y, -_orientation.z, _orientation.w));

	D3DXMatrixMultiply(&_viewMatrix, &translation, &rotation);

	D3DXMatrixInverse(&_billboardMatrix, NULL, &_viewMatrix);

	_billboardMatrix._41 = 0.0f;
	_billboardMatrix._42 = 0.0f;
	_billboardMatrix._43 = 0.0f;

	EVSystem->DirectDevice()->SetTransform(D3DTS_VIEW, &_viewMatrix);
}

void EVCamera::UpdateProjection(int fieldOfView, float aspect, float nearZ, float farZ)
{
	float newFieldOfView = D3DXToRadian(fieldOfView);

	D3DXMatrixPerspectiveFovLH(&_projectionMatrix, newFieldOfView, aspect, nearZ, farZ);

	EVSystem->DirectDevice()->SetTransform(D3DTS_PROJECTION, &_projectionMatrix);
}

void EVCamera::MoveLocalForward(float distance)
{
	_look.x = _viewMatrix._13;
	_look.y = _viewMatrix._23;
	_look.z = _viewMatrix._33;

	_position += _look * distance;
	
	UpdateView();
}

void EVCamera::MoveLocalRight(float distance)
{
	D3DXVECTOR3 right;
	right.x = _viewMatrix._11;
	right.y = _viewMatrix._21;
	right.z = _viewMatrix._31;

	_position += right * distance;

	UpdateView();
}

void EVCamera::MoveLocalUp(float distance)
{
	_up.x = _viewMatrix._12;
	_up.y = _viewMatrix._22;
	_up.z = _viewMatrix._32;

	_position += _up * distance;

	UpdateView();
}

void EVCamera::MoveTo(D3DXVECTOR3 target)
{
	_position = target;

	UpdateView();
}

D3DXVECTOR3* EVCamera::TransformAxis(D3DXQUATERNION* orientation, D3DXVECTOR3* axis)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, orientation);

	D3DXVECTOR3 axisNew;
	axisNew.x = axis->x * rotation._11 + axis->y * rotation._21 + axis->z * rotation._31 + rotation._41;
	axisNew.y = axis->x * rotation._12 + axis->y * rotation._22 + axis->z * rotation._32 + rotation._42;
	axisNew.z = axis->x * rotation._13 + axis->y * rotation._23 + axis->z * rotation._33 + rotation._43;

	memcpy(axis, &axisNew, sizeof(axisNew));
	return axis;
}

void EVCamera::RotateRight(float degree)
{
	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, &EVMath::TransformDirection(&_orientation, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)), D3DXToRadian(degree));

	_orientation *= rot;

	D3DXQuaternionNormalize(&_orientation, &_orientation);

	UpdateView();
}

void EVCamera::RotateForward(float degree)
{
	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, &EVMath::TransformDirection(&_orientation, &D3DXVECTOR3(0.0f, 0.0f, 1.0f)), D3DXToRadian(degree));

	_orientation *= rot;

	D3DXQuaternionNormalize(&_orientation, &_orientation);
	
	UpdateView();
}

void EVCamera::RotateUp(float degree)
{
	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, &EVMath::TransformDirection(&_orientation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)), D3DXToRadian(degree));
	_orientation *= rot;

	D3DXQuaternionNormalize(&_orientation, &_orientation);
	
	UpdateView();
}

bool EVCamera::SmoothRotate(D3DXQUATERNION quatTarget, float speedMultiple)
{
	if (_orientation == quatTarget)
		return false;

	D3DXQuaternionSlerp(&_orientation, &_orientation, &quatTarget, EVTime->DeltaTime() * speedMultiple);
	D3DXQuaternionNormalize(&_orientation, &_orientation);
	
	UpdateView();

	return true;
}

bool EVCamera::SmoothTranslate(D3DXVECTOR3 target, float speedMultiple)
{
	if (_position == target)
	{
		return false;
	}

	D3DXVec3Lerp(&_position, &_position, &target, EVTime->DeltaTime() * speedMultiple);

	UpdateView();

	return true;
}

void EVCamera::Rotation(D3DXQUATERNION rotation)
{
	_orientation = rotation;

	UpdateView();
}

void EVCamera::Rotation(D3DXVECTOR3 rotation)
{
	D3DXQUATERNION quatRotation;
	D3DXQuaternionIdentity(&quatRotation);

	D3DXQuaternionRotationYawPitchRoll(&quatRotation, D3DXToRadian(rotation.y), D3DXToRadian(rotation.x), D3DXToRadian(rotation.z));

	_orientation = quatRotation;

	UpdateView();
}