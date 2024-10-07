#ifndef _EVOLUTIONSPHERECOLLIDER_H_
#define _EVOLUTIONSPHERECOLLIDER_H_

#include "EvolutionCollider.h"

class EVSphereCollider : public EVCollider
{

private:

	float radius;

public:

	EVSphereCollider(float radius = 0.5f);
	~EVSphereCollider();

	void Update();
	void Render(D3DXMATRIX* combinedMatrix = NULL);

public:

	void	Radius(float radius) { this->radius = radius; }
	float	Radius() { return radius; }

};

#endif