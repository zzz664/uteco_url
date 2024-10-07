#ifndef _EVOLUTIONMATH_H_
#define _EVOLUTIONMATH_H_

#include "EvolutionSphereCollider.h"

class EVMath 
{
public:
	static class Vector3 : public D3DXVECTOR3
	{
	public:
		static D3DXVECTOR3 Right()		{ return D3DXVECTOR3(1.0f, 0.0f, 0.0f); }
		static D3DXVECTOR3 Up()			{ return D3DXVECTOR3(0.0f, 1.0f, 0.0f); }
		static D3DXVECTOR3 Forward()	{ return D3DXVECTOR3(0.0f, 0.0f, 1.0f); }
		//static D3DXVECTOR3 Lerp(D3DXVECTOR3 from, D3DXVECTOR3 to, float time);
	};

private:

	EVMath();

public:

	~EVMath();

	static bool SphereToSphereCollision(EVSphereCollider* sphere1, EVSphereCollider* sphere2, D3DXVECTOR3* opposeDir, float* gap);
	static D3DXVECTOR3 TransformDirection(D3DXQUATERNION* orientation, D3DXVECTOR3* direction);
};

#endif