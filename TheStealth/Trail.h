#ifndef _TRAIL_H_
#define _TRAIL_H_

#include "DxObject.h"

class Trail : public DxObject
{

public:

	struct VertexType
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR4	color;
	};

private:

	LPDIRECT3DDEVICE9 device;

	VertexType		v[4];

	VertexType*		rom1;
	VertexType*		rom2;

	VertexType*		trail;

	int					slices;
	float				scale;

public:

	Trail(int slices = 20, float scale = 1.0f);
	~Trail();

	void Update(float eTime);
	void Render();
};

#endif