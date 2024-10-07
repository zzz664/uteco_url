#ifndef _EVOLUTIONMODEL_H_
#define _EVOLUTIONMODEL_H_

#include "EvolutionGameObject.h"
#include "EvolutionDiffuseTexture.h"

#include <string>

class EVModel : public EVGameObject
{

private:

	LPD3DXMESH				_mesh;
	D3DMATERIAL9*			_meshMaterials;
	LPDIRECT3DTEXTURE9*		_meshTextures;

	EVDiffuseTexture*		_diffuseTexture;

	DWORD					_numMaterials;

public:

	EVModel(std::string path);
	~EVModel();

	void Update();
	void Render(D3DXMATRIX* combinedMatrix = NULL);
};

#endif