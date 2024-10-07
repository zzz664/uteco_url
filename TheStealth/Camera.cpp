#include "Camera.h"
#include "DirectX9.h"

Camera::Camera()
{
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXQuaternionIdentity(&orientation);

	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projectionMatrix);
	D3DXMatrixIdentity(&billboardMatrix);

	shakeRad = 0.0f;

	UpdateView();
	UpdateProjection(50 * DirectX9->GetAspect(), DirectX9->GetScreenWidth() / DirectX9->GetScreenHeight(), 1.0f, 10000.0f);
}

Camera::~Camera()
{
}

bool Camera::Shake(float eTime, float shakeFrequency, float shakeSpeed, float shakeFactor)
{
	if (shakeRad >= D3DX_PI)
	{
		shakeRad = 0.0f;
		return false;
	}

	shakeRad += shakeSpeed * eTime;

	position.x = cos(shakeRad * shakeFrequency / 3) * pow(shakeFactor, shakeRad);
	position.y = sin(shakeRad * shakeFrequency) * pow(shakeFactor, shakeRad);

	UpdateView();

	return true;
}

void Camera::MoveTo(float x, float y, float z)
{
	position = D3DXVECTOR3(x, y, z);

	UpdateView();
}

void Camera::MoveLocalX(float distance)
{
	D3DXVECTOR3 right;
	right.x = viewMatrix._11;
	right.y = viewMatrix._21;
	right.z = viewMatrix._31;

	position += right * distance;

	UpdateView();
}

void Camera::MoveLocalY(float distance)
{
	up.x = viewMatrix._12;
	up.y = viewMatrix._22;
	up.z = viewMatrix._32;

	position += up * distance;

	UpdateView();
}

void Camera::MoveLocalZ(float distance)
{
	look.x = viewMatrix._13;
	look.y = viewMatrix._23;
	look.z = viewMatrix._33;

	position += look * distance;

	UpdateView();
}

void Camera::RotateX(float degree)
{
	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, TransformDirection(&orientation, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)), D3DXToRadian(degree));

	orientation *= rot;

	D3DXQuaternionNormalize(&orientation, &orientation);

	UpdateView();
}

void Camera::RotateY(float degree)
{
	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, TransformDirection(&orientation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)), D3DXToRadian(degree));
	orientation *= rot;

	D3DXQuaternionNormalize(&orientation, &orientation);

	UpdateView();
}

void Camera::RotateZ(float degree)
{
	D3DXQUATERNION rot;

	D3DXQuaternionRotationAxis(&rot, TransformDirection(&orientation, &D3DXVECTOR3(0.0f, 0.0f, 1.0f)), D3DXToRadian(degree));

	orientation *= rot;

	D3DXQuaternionNormalize(&orientation, &orientation);

	UpdateView();
}

void Camera::UpdateView()
{
	CalcDirectionVector();

	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, -position.x, -position.y, -position.z);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &D3DXQUATERNION(-orientation.x, -orientation.y, -orientation.z, orientation.w));

	D3DXMatrixMultiply(&viewMatrix, &translation, &rotation);

	DirectX9->GetDevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::UpdateProjection(int fieldOfView, float aspect, float nearZ, float farZ)
{
	float newFieldOfView = D3DXToRadian(fieldOfView);

	D3DXMatrixPerspectiveFovLH(&projectionMatrix, newFieldOfView, aspect, nearZ, farZ);

	DirectX9->GetDevice()->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

void Camera::UpdateProjection2(float fieldOfView, float aspect, float nearZ, float farZ)
{
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, aspect, nearZ, farZ);

	DirectX9->GetDevice()->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

D3DXMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}

D3DXMATRIX Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

D3DXMATRIX Camera::GetBillboardALL()
{
	D3DXMatrixIdentity(&billboardMatrix);

	billboardMatrix._11 = viewMatrix._11;
	billboardMatrix._12 = viewMatrix._12;
	billboardMatrix._13 = viewMatrix._13;

	billboardMatrix._21 = viewMatrix._21;
	billboardMatrix._22 = viewMatrix._22;
	billboardMatrix._23 = viewMatrix._23;

	billboardMatrix._31 = viewMatrix._31;
	billboardMatrix._32 = viewMatrix._32;
	billboardMatrix._33 = viewMatrix._33;

	D3DXMatrixInverse(&billboardMatrix, NULL, &billboardMatrix);

	billboardMatrix._41 = 0.0f;
	billboardMatrix._42 = 0.0f;
	billboardMatrix._43 = 0.0f;

	return billboardMatrix;
}

D3DXMATRIX Camera::GetBillboardX()
{
	D3DXMatrixIdentity(&billboardMatrix);

	billboardMatrix._22 = viewMatrix._22;
	billboardMatrix._23 = viewMatrix._23;
	billboardMatrix._32 = viewMatrix._32;
	billboardMatrix._33 = viewMatrix._33;

	D3DXMatrixInverse(&billboardMatrix, NULL, &billboardMatrix);

	billboardMatrix._41 = 0.0f;
	billboardMatrix._42 = 0.0f;
	billboardMatrix._43 = 0.0f;

	return billboardMatrix;
}

D3DXMATRIX Camera::GetBillboardY()
{
	D3DXMatrixIdentity(&billboardMatrix);

	billboardMatrix._11 = viewMatrix._11;
	billboardMatrix._13 = viewMatrix._13;
	billboardMatrix._31 = viewMatrix._31;
	billboardMatrix._33 = viewMatrix._33;

	D3DXMatrixInverse(&billboardMatrix, NULL, &billboardMatrix);

	billboardMatrix._41 = 0.0f;
	billboardMatrix._42 = 0.0f;
	billboardMatrix._43 = 0.0f;

	return billboardMatrix;
}

D3DXMATRIX Camera::GetBillboardZ()
{
	D3DXMatrixIdentity(&billboardMatrix);

	billboardMatrix._11 = viewMatrix._11;
	billboardMatrix._12 = viewMatrix._12;
	billboardMatrix._21 = viewMatrix._21;
	billboardMatrix._22 = viewMatrix._22;

	D3DXMatrixInverse(&billboardMatrix, NULL, &billboardMatrix);

	billboardMatrix._41 = 0.0f;
	billboardMatrix._42 = 0.0f;
	billboardMatrix._43 = 0.0f;

	return billboardMatrix;
}

D3DXVECTOR3* Camera::TransformAxis(D3DXQUATERNION* orientation, D3DXVECTOR3* axis)
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

D3DXVECTOR3* Camera::TransformDirection(D3DXQUATERNION* orientation, D3DXVECTOR3* direction)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, orientation);

	D3DXVECTOR3 newDirection;
	newDirection.x = direction->x * rotation._11 + direction->y * rotation._21 + direction->z * rotation._31 + rotation._41;
	newDirection.y = direction->x * rotation._12 + direction->y * rotation._22 + direction->z * rotation._32 + rotation._42;
	newDirection.z = direction->x * rotation._13 + direction->y * rotation._23 + direction->z * rotation._33 + rotation._43;

	memcpy(direction, &newDirection, sizeof(newDirection));

	return direction;
}

void Camera::CalcDirectionVector()
{
	right = *TransformDirection(&orientation, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	up = *TransformDirection(&orientation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	look = *TransformDirection(&orientation, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void Camera::SmoothRotate(D3DXQUATERNION quatTarget, float speedMultiple, float eTime)
{
	if (orientation == quatTarget)
		return;

	D3DXQuaternionSlerp(&orientation, &orientation, &quatTarget, eTime * speedMultiple);
	D3DXQuaternionNormalize(&orientation, &orientation);

	UpdateView();
}

void Camera::SmoothTranslate(D3DXVECTOR3 target, float speedMultiple, float eTime)
{
	if (position == target)
	{
		return;
	}

	D3DXVec3Lerp(&position, &position, &target, eTime * speedMultiple);

	UpdateView();
}