#include "EvolutionSphereCollider.h"
#include "EvolutionCore.h"

EVSphereCollider::EVSphereCollider(float radius)
{
	this->radius = radius;

	EVSystem->DirectDevice()->CreateVertexBuffer(
		sizeof(COLLIDERVERTEX) * 36,
		0, 
		D3DFVF_COLLIDER,
		D3DPOOL_DEFAULT, 
		&_vertexBuffer, 
		NULL);
}

EVSphereCollider::~EVSphereCollider()
{

}

void EVSphereCollider::Update()
{
	EVCollider::Update();
}

void EVSphereCollider::Render(D3DXMATRIX* combinedMatrix)
{
	EVCollider::Render(combinedMatrix);

	EVCollider::DrawSphereCollider(_vertexBuffer, radius);
}