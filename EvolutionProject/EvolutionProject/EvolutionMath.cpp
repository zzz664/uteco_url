#include "EvolutionMath.h"

EVMath::EVMath()
{

}

EVMath::~EVMath()
{

}

D3DXVECTOR3 EVMath::TransformDirection(D3DXQUATERNION* orientation, D3DXVECTOR3* direction)
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

bool EVMath::SphereToSphereCollision(EVSphereCollider* sphere1, EVSphereCollider* sphere2, D3DXVECTOR3* opposeDir, float* gap)
{
	double distance1 = 0.0f;
	double distance2 = 0.0f;

	distance1 = pow(sphere2->TransformMatrix()._41 - sphere1->TransformMatrix()._41, 2);
	distance1 += pow(sphere2->TransformMatrix()._42 - sphere1->TransformMatrix()._42, 2);
	distance1 += pow(sphere2->TransformMatrix()._43 - sphere1->TransformMatrix()._43, 2);

	distance2 = pow(sphere1->Radius() + sphere2->Radius(), 2);

	*gap = distance2 - distance1;

	D3DXVECTOR3 posSphere1(sphere1->TransformMatrix()._41, sphere1->TransformMatrix()._42, sphere1->TransformMatrix()._43);
	D3DXVECTOR3 posSphere2(sphere2->TransformMatrix()._41, sphere2->TransformMatrix()._42, sphere2->TransformMatrix()._43);

	*opposeDir = posSphere2 - posSphere1;
	D3DXVec3Normalize(opposeDir, opposeDir);

	if (distance1 < distance2)
	{
		return true;
	}

	return false;
}