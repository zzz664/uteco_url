#ifndef _EVOLUTIONBOX_H_
#define _EVOLUTIONBOX_H_

#include "EvolutionGameObject.h"
#include "EvolutionDiffuse.h"

#include <string>

class EVShape : public EVGameObject
{

private:

	LPD3DXMESH	_mesh;
	EVDiffuse*	_diffuse;

public:

	EVShape(std::string shape = "Cube", D3DXCOLOR ambientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	~EVShape();

	void Update();
	void Render(D3DXMATRIX* combinedMatrix = NULL);

public:

	void		Color(D3DXCOLOR ambientColor)	{ _diffuse->Ambient(ambientColor); }
	D3DXCOLOR	Color()							{ return _diffuse->Ambient(); }

};

#endif