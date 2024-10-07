#ifndef _EVOLUTIONTRAIL_H_
#define _EVOLUTIONTRAIL_H_

#include "EvolutionGameObject.h"

struct TRAILVERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex;
};

class EVTrail : public EVGameObject
{

private:

	LPDIRECT3DTEXTURE9	_texture;

	TRAILVERTEX			_v[4];

	TRAILVERTEX*		_rom1;
	TRAILVERTEX*		_rom2;
	TRAILVERTEX*		_trail;

	int					_slices;
	float				_scale;

public:

	EVTrail(std::string path, int slices = 20, float scale = 1.0f);
	~EVTrail();

	void Update();
	void Render();
};

#endif