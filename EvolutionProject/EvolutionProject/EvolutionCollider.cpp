#include "EvolutionCollider.h"
#include "EvolutionCore.h"

EVCollider::EVCollider()
{
	_vertexBuffer = NULL;
}

EVCollider::~EVCollider()
{
	_vertexBuffer->Release();
}

void EVCollider::Update()
{
	EVGameObject::Update();
}

void EVCollider::Render(D3DXMATRIX* combinedMatrix)
{
	EVGameObject::Render(combinedMatrix);
}



void EVCollider::DrawCircleX(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius)
{
	COLLIDERVERTEX vertices[37];

	for (int i = 0; i <= 36; ++i)
	{
		vertices[i].x = 0;
		vertices[i].y = radius * sin(D3DXToRadian(i * 10));
		vertices[i].z = radius * cos(D3DXToRadian(i * 10));
		vertices[i].color = D3DCOLOR_RGBA(0, 255, 0, 255);
	}

	void* source;
	vertexBuffer->Lock(0, sizeof(vertices), &source, 0);
	memcpy(source, vertices, sizeof(vertices));
	vertexBuffer->Unlock();

	EVSystem->DirectDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(COLLIDERVERTEX));
	EVSystem->DirectDevice()->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));
	EVSystem->DirectDevice()->DrawPrimitive(D3DPT_LINESTRIP, 0, 37);
}

void EVCollider::DrawCircleY(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius)
{
	COLLIDERVERTEX vertices[37];

	for (int i = 0; i <= 36; ++i)
	{
		vertices[i].x = radius * sin(D3DXToRadian(i * 10));
		vertices[i].y = 0;
		vertices[i].z = radius * cos(D3DXToRadian(i * 10));
		vertices[i].color = D3DCOLOR_RGBA(0, 255, 0, 255);
	}

	void* source;
	vertexBuffer->Lock(0, sizeof(vertices), &source, 0);
	memcpy(source, vertices, sizeof(vertices));
	vertexBuffer->Unlock();

	EVSystem->DirectDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(COLLIDERVERTEX));
	EVSystem->DirectDevice()->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));
	EVSystem->DirectDevice()->DrawPrimitive(D3DPT_LINESTRIP, 0, 37);
}

void EVCollider::DrawCircleZ(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius)
{
	COLLIDERVERTEX vertices[37];

	for (int i = 0; i <= 36; ++i)
	{
		vertices[i].x = radius * cos(D3DXToRadian(i * 10));
		vertices[i].y = radius * sin(D3DXToRadian(i * 10));
		vertices[i].z = 0;
		vertices[i].color = D3DCOLOR_RGBA(0, 255, 0, 255);
	}

	void* source;
	vertexBuffer->Lock(0, sizeof(vertices), &source, 0);
	memcpy(source, vertices, sizeof(vertices));
	vertexBuffer->Unlock();

	EVSystem->DirectDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(COLLIDERVERTEX));
	EVSystem->DirectDevice()->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));
	EVSystem->DirectDevice()->DrawPrimitive(D3DPT_LINESTRIP, 0, 37);
}

void EVCollider::DrawSphereCollider(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, float radius)
{
	EVSystem->DirectDevice()->SetRenderState(D3DRS_LIGHTING, false);

	DrawCircleX(vertexBuffer, radius);
	DrawCircleY(vertexBuffer, radius);
	DrawCircleZ(vertexBuffer, radius);

}