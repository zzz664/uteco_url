#include "EvolutionModel.h"
#include "EvolutionCore.h"

EVModel::EVModel(std::string path)
{
	LPD3DXBUFFER mtrlBuffer;

	D3DXLoadMeshFromXA(
		path.c_str(), 
		D3DXMESH_SYSTEMMEM, 
		EVSystem->DirectDevice(), 
		NULL, 
		&mtrlBuffer, 
		NULL, 
		&_numMaterials, 
		&_mesh);

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

	_meshMaterials = new D3DMATERIAL9[_numMaterials];
	_meshTextures = new LPDIRECT3DTEXTURE9[_numMaterials];

	for (DWORD i = 0; i<_numMaterials; i++)
	{
		_meshMaterials[i] = d3dxMaterials[i].MatD3D;

		_meshMaterials[i].Ambient = _meshMaterials[i].Diffuse;

		_meshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL 
			&& strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFileA(
				EVSystem->DirectDevice(), 
				d3dxMaterials[i].pTextureFilename, 
				&_meshTextures[i]);
		}
	}

	_diffuseTexture = new EVDiffuseTexture(_meshTextures[0]);
	PushChildObject(_diffuseTexture, "DiffuseTextureShader");

	mtrlBuffer->Release();
}

EVModel::~EVModel()
{
	if (_meshMaterials)
	{
		delete[] _meshMaterials;
	}

	if (_meshTextures)
	{
		for (DWORD i = 0; i<_numMaterials; i++)
		{
			if (_meshTextures[i])
			{
				_meshTextures[i]->Release();
			}
		}
		delete[] _meshTextures;
	}
}

void EVModel::Update()
{
	EVGameObject::Update();
}

void EVModel::Render(D3DXMATRIX* combinedMatrix)
{
	EVGameObject::Render(combinedMatrix);

	for (DWORD i = 0; i<_numMaterials; i++) 
	{
		//EVSystem->DirectDevice()->SetMaterial(&_meshMaterials[i]);

		_diffuseTexture->Ambient(_meshMaterials[i].Ambient);
		_diffuseTexture->Texture(_meshTextures[i]);

		UINT numPasses = 0;

		_diffuseTexture->Start(&numPasses);

		for (int j = 0; j < numPasses; ++j)
		{
			_diffuseTexture->Shader()->BeginPass(j);
			{
				_mesh->DrawSubset(i);
			}
			_diffuseTexture->Shader()->EndPass();
		}

		_diffuseTexture->End();
	}
}