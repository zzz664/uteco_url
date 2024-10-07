#ifndef _EVOLUTIONCOLLIDER_H_
#define _EVOLUTIONCOLLIDER_H_

#include "EvolutionGameObject.h"

#define D3DFVF_COLLIDER (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct COLLIDERVERTEX
{
	float x, y, z;
	DWORD color;
};

class EVCollider : public EVGameObject
{
	
protected:

	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;

public:

	EVCollider();
	virtual ~EVCollider();

	virtual void Update();
	virtual void Render(D3DXMATRIX* combinedMatrix = NULL);

protected:

	static void DrawCircleX(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius = 0.5f);
	static void DrawCircleY(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius = 0.5f);
	static void DrawCircleZ(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius = 0.5f);
	static void DrawSphereCollider(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius = 0.5f);

};

#endif